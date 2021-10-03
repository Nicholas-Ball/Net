#include <iostream>
#include <string>
#include <fstream>


class net{
    private:
        std::string Data;
    public:
        //Get request
        void Get(std::string url)
        {
            //get url
            const std::string command = "curl -G -s "+url+" -o temp.tmp";
            system(command.c_str());

            std::ifstream file("temp.tmp");

            this->Data = "";
            std::string line;

            //add data to self
            while(getline(file,line))
            {
                this->Data += line;
            }

            //close file and delete it
            file.close();
            remove("temp.tmp");
        }

        //Post request
        void Post(std::string url, std::string data);
        
        //data accsessor
        std::string GetData()
        {
            return this->Data;
        }
};
