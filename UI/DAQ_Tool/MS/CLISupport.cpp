#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

using std::cout;
using std::ofstream;
using std::string;
using std::endl;


/*
timeFunction is a calss that retrieves the current time as a string in
the same fomrat "%Y-%m-%d %H:%m:%S" with different precisions:
        - Seconds
        - Milliseconds
        - Microseconds
        - Nanoseconds
*/
class timeFunction {
    private:
      const char timeFormat[18]= "%Y-%m-%d %H:%M:%S";
    public:
      /*precision is to retrive time with seconds(s), milliseconds(mls),
      microseconds (mcs) and nanoseconds (ns)
      */
      enum class precision
      {
        s, mls, mcs, ns
      };
      precision timePrecision;
      timeFunction (precision prec = precision::s){
        timePrecision = prec;
      };

      string getTimeNow(){
        /* chrono::system_clock::now() is a function returns time as a
        chrono::system_clock::time_point object since epoch start couting
        time.
        chrono::system_clock::to_time_t is used to convert time_point to
        a calendar time.
        std::stringstream is a func allows you reading and writing from a
        string. It helps a lot converting between diffrent formats.
        std::localtime: Converts given time since epoch as std::time_t value
         into calendar time, expressed in local time.
         std::put_time: inserts formated time value to an output stream.
        */
        auto currentTime = std::chrono::system_clock::now();
        auto calTime = std::chrono::system_clock::to_time_t(currentTime);
        std::stringstream ss;

        switch (timePrecision){
          case timeFunction::precision::s:{
            ss << std::put_time(std::localtime(&calTime), timeFormat);
            break;
          }

          case timeFunction::precision::mls:{
            auto highResTimeMls = std::chrono::duration_cast<std::chrono::milliseconds> (currentTime.time_since_epoch())%1000;
            ss << std::put_time(std::localtime(&calTime), timeFormat)<<"."<<highResTimeMls.count();
            break;
          }

          case timeFunction::precision::mcs:{
            auto highResTimeMcs = std::chrono::duration_cast<std::chrono::microseconds> (currentTime.time_since_epoch())%1000000;
            ss << std::put_time(std::localtime(&calTime), timeFormat)<<"."<<highResTimeMcs.count();
            break;
          }

          case timeFunction::precision::ns:{
            auto highResTimeNs = std::chrono::duration_cast<std::chrono::nanoseconds> (currentTime.time_since_epoch())%1000000000;
            ss << std::put_time(std::localtime(&calTime), timeFormat)<<"."<<highResTimeNs.count();
            break;
          }
      }

        return ss.str();
      }

      };

class Message
{
private:
        virtual void show(string message, string type) = 0;
        string infoMsgOptions [3];
        string errorMsgOptions [3];
        string warningMsgOptions [3];
        string criticalMsgOptions [2];

        void initMsgOptions (){
                infoMsgOptions [0] = "i";
                infoMsgOptions [1] = "info";
                infoMsgOptions [2] = "information";
                errorMsgOptions [0] = "e" ;
                errorMsgOptions [1] = "err";
                errorMsgOptions [2] = "error";
                warningMsgOptions [0] = "w";
                warningMsgOptions [1] = "war";
                warningMsgOptions [2] = "warning";
                criticalMsgOptions [0] = "c";
                criticalMsgOptions [1] = "critical";
        }

        string toLowerCase(const string& str) {
          // Create a copy of the string and convert all characters to lowercase
          string lowercase_str = str;
          transform(lowercase_str.begin(), lowercase_str.end(), lowercase_str.begin(), ::tolower);
          return lowercase_str;
        }

protected:
        enum messageID{
                I = 1, // information message
                W = 2, // Worning Message
                E = 3, // Error message
                C = 4, // Critical
                U = 5  // Unknown
        };

        int msgInterpretation(){
          bool found = false;
          messageID var_messageID;
      if (find (begin(infoMsgOptions), end(infoMsgOptions), toLowerCase(Type) ) != end(infoMsgOptions)){
         found = true;
         var_messageID = I;
      }
      else if (find (begin(warningMsgOptions), end(warningMsgOptions), toLowerCase(Type) ) != end(warningMsgOptions)){
         found = true;
         var_messageID = W;
      }
      else if (find (begin(errorMsgOptions), end(errorMsgOptions), toLowerCase(Type) ) != end(errorMsgOptions)){
         found = true;
         var_messageID = E;
      }
      else if (find (begin(criticalMsgOptions), end(criticalMsgOptions), toLowerCase(Type) ) != end(criticalMsgOptions)){
         found = true;
         var_messageID = C;
      }
      else {
        var_messageID = U;
      }

      return var_messageID;
        }

public:
        string Msg; // message text
        string Type;
        string logFile;
        //Message Constructor
        Message(string message, string type) {
                Msg = message;
                Type = type;
                this -> initMsgOptions();
                this -> msgInterpretation();
        }
};

class CLIMessage:public Message
{
public:
        CLIMessage(string message = "None", string type = "U"):Message(message, type){

        }
        // ~CLIMessage();

        void show(string message,  string type = "U"){
                Msg = message;
                Type = type;

                int interpretedMsg = msgInterpretation ();

                switch (interpretedMsg){
                case 1:
                        cout << "\033[0;32m" << Msg << "\033[0m" << endl;
                        break;
                case 2:
                        cout << "\033[0;33m" << Msg << "\033[0m" << endl;
                        break;
                case 3:
                        cout << "\033[1;31m" << Msg << "\033[0m" << endl;
                        break;
                case 4:
                        cout << "\033[37;41m" << "Critical:: " << Msg << "\033[0m" << endl;
                        break;
                case 5:
                        cout << "\033[1;34m" << Msg << "\033[0m" << endl;
                        break;
                }
        }
};

class LogMessage:public Message
{
public:
   timeFunction timeStamp = timeFunction(timeFunction::precision::mcs);
        LogMessage(string message = "None", string type = "U"):Message(message, type){

        }
        void setupLoggerFile(const string& filePath){
                
                logFile = filePath;
                ofstream file(filePath);
                if (!file.is_open()) {
                        // Handle error if file cannot be opened
                        return;
                }

                file << "";
                file.close();
        }

        void writeLogs(const string& log){
                
                ofstream outputFile(logFile, std::ios::app);  // Open the file in append mode
                outputFile << log << "\n";
				outputFile.close();
        }

        void show(string message,  string type = "U"){
                Msg = message;
                Type = type;
				string log;

                int interpretedMsg = msgInterpretation ();
                switch (interpretedMsg){
                case 1:
						log = "\033[0;32m" + timeStamp.getTimeNow() + Msg + "\033[0m";
                        cout << log << endl;
                        break;
                case 2:
						log = "\033[0;33m" + timeStamp.getTimeNow() + Msg + "\033[0m";
                        cout << log << endl;
                        break;
                case 3:
						log = "\033[1;31m" + timeStamp.getTimeNow() + Msg + "\033[0m";
                        cout << log << endl;
                        break;
                case 4:
						log = "\033[37;41m" + timeStamp.getTimeNow() + Msg + "\033[0m";
                        cout << log << endl;
                        break;
                case 5:
						log = "\033[1;34m" + timeStamp.getTimeNow() + Msg + "\033[0m";
                        cout << log << endl;
                        break;
                }

				writeLogs(log);
        }
};


//int main(int argc, char const *argv[])
//{
//        CLIMessage cliMsg;
//        LogMessage logMsg;

//        logMsg.show("This is an information log message", "info");
//        logMsg.show("This is a warning log message", "w");
//        logMsg.show("This is an error log message", "e");
//        logMsg.show("This is a critical log message", "c");

//        return 0;
//}
