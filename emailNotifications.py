import zmq
from SEDSS.SEDFileManager import readFile

emailNotificationFile = "configurations/emailNotification.json"
scheduledProposalFile = "metadata/MSScheduledProposals.csv"
emailNotification = readFile(emailNotificationFile).readJSON()

sender		  = emailNotification["sender"]
subjectPrefix = emailNotification["subjectPrefix"]
signature     = emailNotification["signature"]

class email:
	"""
	email:
	- connect to the mail server.
	- get the proposal info (name, email, title) if the experiment is 'Users Experiment'.
	- define the experiment template depending on experiment type.
	"""
	def __init__(self, experimentType, proposalID=None):

		self.context = zmq.Context()
		self.socket = self.context.socket(zmq.PUSH)
		self.socket.connect(emailNotification["mailServer"])

		if experimentType.strip() == "Users":
			self.userExperiment = True
			self.proposer, self.email, self.title = readFile(scheduledProposalFile).getProposalInfo(proposalID)
			self.experimentTypeBody = str(f"Dear {self.proposer},\n\n"
											f"Proposal Data:\n"
											f"{'='*30}\n"
											f"Proposal ID: {proposalID}\n"
											f"Beamline: {emailNotification['beamline']}.\n"
											f"Proposal Title: {self.title}.\n\n")
		else:
			self.userExperiment = False
			self.experimentTypeBody = str(f"Experiment:\n"
											f"{'='*30}\n"
											f"Type: {emailNotification['localExperiment']}\n"
											f"Beamline: {emailNotification['beamline']}\n\n")

	def msgTemplate(self, info, sevr, reason, action, DS, template="standard"):
		"""
		msgTemplate:
		- return the standard message template (except defined templates).
		"""

		ds = "\n" if DS == "Not defined" else f"Data Destination: {DS}.\n\n"

		if template in emailNotification["notesTemplates"]:

			if reason is None:
				reason = emailNotification[template]['note']

			return self.experimentTypeBody + str(f"Status: \n"
													f"{'='*30}\n"
													f"Information: {info}.\n"
													f"Severity: {sevr}\n"
													f"Note: {reason}.\n"
													f"{ds}"
													f"{signature}")
		elif template in emailNotification["veryImportantTemplates"]:
			return self.experimentTypeBody + "*** VERY IMPORTANT!***\n" + str(f"Status:\n"
																				f"{'='*30}\n"
																				f"Information: {info}.\n"
																				f"Severity: {sevr}\n"
																				f"Reason: {reason}.\n"
																				f"Action / Details: {action}.\n"
																				f"{ds}"
																				f"{signature}")
		else:
			return self.experimentTypeBody + str(f"Status: \n"
													f"{'='*30}\n"
													f"Information: {info}.\n"
													f"Severity: {sevr}\n"
													f"Reason: {reason}.\n"
													f"Action / Details: {action}.\n"
													f"{ds}"
													f"{signature}")

	def sendEmail(self, type, msg=None, PV=None, DS="Not defined"):
		"""
		sendEmail:
		- prepare the email parameters from a configuration file.
		- send the email.
		"""
		recipient, recipientNames = self.emailList(emailNotification[type]['recipients'])
		CCAddresses, CCAddressesNames = self.emailList(emailNotification[type]["CCAddresses"])
		subject = f"{emailNotification['subjectPrefix']} {emailNotification[type]['subject']}"
		severity = self.severity(emailNotification[type]['severity'])

		# try & except (there are messages come with a specific information)
		try:
			information = self.information(emailNotification[type]['information'])
		except:
			information = emailNotification[type]['information']

		# try & except (there are messages come without action)
		try:
			action = emailNotification[type]['action']
		except:
			action = None

		pv = "" if PV is None else f"({PV})"

		if type in emailNotification["specificTemplates"]:
			msg = self.msgTemplate(information, severity, msg, action, DS, type)
		else:
			msg = self.msgTemplate(information, severity, f"{emailNotification[type]['reason']} {pv}", action, DS)

		if self.userExperiment:
			recipients = f"{self.email};{recipient}"
			body = msg
		else:
			recipients = recipient
			body = str(f"Dears {recipientNames}\n\n") + msg

		self.socket.send_multipart([sender.encode(), recipients.encode(), CCAddresses.encode(), subject.encode(), body.encode()])
		self.close()

	def emailList(self, email):

		if email.strip() != "":
			emails = email.split(', ')
			emailsList = ""
			emailsNames = ""
			for one in emails:
				emailsList = emailsList + emailNotification["emails"][one]
				emailsNames = emailsNames + emailNotification["names"][one]
			return emailsList, emailsNames
		else:
			return "", ""

	def information(self, info):
		return emailNotification["information"][info]

	def severity(self, sevr):
		return emailNotification["severity"][int(sevr)]

	def close(self):
		self.socket.close()
		self.context.term()
