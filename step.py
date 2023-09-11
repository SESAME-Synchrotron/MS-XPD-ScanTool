from MS import XPD

class step(XPD):
	def __init__(self, PVsFiles, macros, scanningSubs):
		super().__init__(PVsFiles, macros, scanningSubs)

		self.preCheck()
		self.initDir()
		self.detectorInit()

	def preCheck(self):
		super().preCheck()