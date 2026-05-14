#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Convert string to lowercase
string toLowerCase(string text)
{
    transform(text.begin(), text.end(), text.begin(), ::tolower);
    return text;
}

// Chatbot response function
void chatbotResponse(string input)
{
    input = toLowerCase(input);

    if(input.find("hello") != string::npos ||
       input.find("hi") != string::npos)
    {
        cout << "Bot: Hello! Welcome to Railway Support Service.\n";
    }

    else if(input.find("ticket") != string::npos ||
            input.find("booking") != string::npos)
    {
        cout << "Bot: Ticket booking is available from 6 AM to 11 PM.\n";
    }

    else if(input.find("timing") != string::npos ||
            input.find("train") != string::npos)
    {
        cout << "Bot: Please visit the station inquiry counter for exact timings.\n";
    }

    else if(input.find("cancel") != string::npos)
    {
        cout << "Bot: Ticket cancellation can be done online or at reservation counters.\n";
    }

    else if(input.find("fare") != string::npos ||
            input.find("price") != string::npos)
    {
        cout << "Bot: Fare depends on class and destination.\n";
    }

    else if(input.find("help") != string::npos)
    {
        cout << "Bot: You can ask about booking, cancellation, fare, or train timing.\n";
    }

    else
    {
        cout << "Bot: Sorry, I could not understand your query.\n";
    }
}

int main()
{
    string input;

    cout << "=====================================\n";
    cout << " Railway Reservation Chatbot\n";
    cout << "=====================================\n";

    cout << "Type 'exit' to end conversation.\n";

    while(true)
    {
        cout << "\nYou: ";
        getline(cin, input);

        string lowerInput = toLowerCase(input);

        if(lowerInput == "exit")
        {
            cout << "Bot: Thank you for using Railway Support Service.\n";
            break;
        }

        chatbotResponse(input);
    }

    return 0;
}