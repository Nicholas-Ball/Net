#include <iostream>
#include <string>
#include <fstream>
#include <thread>
#include <chrono>
#include <sys/stat.h>

#ifdef _WIN32
#include <windows.h>
#endif


//checks if file exits
inline bool Exists (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

//runs command without popup cross platform
std::string run(const char* command)
{   
   char buffer[128];
   std::string result = "";

   // Open pipe to file
   FILE* pipe = popen(command, "r");

   // read till end of process:
   while (!feof(pipe)) {

      // use buffer to read and add to result
      if (fgets(buffer, 128, pipe) != NULL)
         result += buffer;
   }

  pclose(pipe);
  return result;
}

class net{
    private:
        //resposne of curl
        std::string Data;

        //status code
        std::string Code;
    public:
        //constructor
        net()
        {
          srand(time(NULL));
        }

        //Get request
        void Get(std::string url,int delay = 0)
        {
          //make a temp file for response
          int r1 = (int)(rand() % 9999999999);
          std::string f1 = std::to_string(r1) + ".tmp";
          srand(r1);

          //get url and set status code
          const std::string command = ("curl -m 30 -X GET -s -o "+f1+" -w \"%{http_code}\" \""+url+"\"");
          this->Code = run(command.c_str());

          //Read response
          std::ifstream file(f1);
          this->Data = "";
          std::string line;

          //add response to data var
          while(getline(file,line))
          {
            this->Data += line;
          }

          //close file and delete it
          file.close();
          remove(f1.c_str());
        }

        //Post request
        void Post(std::string url, std::string data,int delay = 0)
        {
          //make a temp file for response
          int r1 = (int)(rand() % 9999999999);
          std::string f1 = std::to_string(r1) + ".tmp";
          srand(r1);

          //post to url and set status code
          const std::string command = ("curl -X POST -d "+data+" -s -o "+f1+" -w \"%{http_code}\" \""+url+"\"");
          this->Code = run(command.c_str());

          //Read response
          std::ifstream file(f1);
          this->Data = "";
          std::string line;

          //add response to data var
          while(getline(file,line))
          {
            this->Data += line;
          }

          //close file and delete it
          file.close();
          remove(f1.c_str());
        }

        //Response accsessor
        std::string Response()
        {
            return this->Data;
        }

        //Status Code accsessor
        std::string StatusCode()
        {
            return this->Code;
        }
};