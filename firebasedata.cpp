#include <iostream>
#include <curl/curl.h>
#include <string>

// Function to send data to Firebase using HTTP POST
bool sendDataToFirebase(const std::string& url, const std::string& data) {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set HTTP POST data
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

        // Specify content-type header
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Perform the request, res will get the return code
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Data sent successfully!" << std::endl;
        }

        // Cleanup
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    curl_global_cleanup();
    return res == CURLE_OK;
}

int main() {
    // Firebase URL and API key (replace with your own database URL and API key)
    std::string firebase_url = "https://your-database-name.firebaseio.com/users.json"; // Replace with your Firebase database URL
    std::string api_key = "your-api-key"; // Replace with your Firebase API key if required for authentication

    // Data to send (in JSON format)
    std::string user_data = R"({
        "name": "John Doe",
        "email": "john.doe@example.com"
    })";

    // Construct the full URL with the API key if necessary
    std::string full_url = firebase_url + "?auth=" + api_key;

    // Send data to Firebase
    if (sendDataToFirebase(full_url, user_data)) {
        std::cout << "Data was sent successfully to Firebase." << std::endl;
    } else {
        std::cerr << "Failed to send data to Firebase." << std::endl;
    }

    return 0;
}
