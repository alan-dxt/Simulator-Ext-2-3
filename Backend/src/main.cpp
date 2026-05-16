#include <iostream>
#include "./httplib.h"

#include "./Routes/RoutesReader.h"

using namespace std;

int main(){
    httplib::Server api;

    //Endpoitn for the console
    RoutesReader::Reader(api);

    api.Get("/", [](const httplib::Request& req, httplib::Response& res){
        cout<<"Hello world";
        res.set_content("Api rest c++ ok", "text/plain");
    });

    cout<<"Working on http://localhost:8080\n";
    api.listen("0.0.0.0", 8080);
    return 0;
}