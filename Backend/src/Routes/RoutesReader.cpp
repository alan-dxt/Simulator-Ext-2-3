#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>
#include <map>
#include <vector>
#include "../httplib.h"
#include "../Objects/Command.h"
#include "../Objects/CommandResult.h"
#include "./RoutesReader.h"

using json = nlohmann::json;

using namespace std;

string Trim(const string& str){
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \n\n\r");
    if(first == string::npos) return "";
    return str.substr(first, (last - first +1));
}

vector<Command> splitCommands(const string& data){
    stringstream rawData(data);
    std::string line;
    vector<Command> commands; 
    //The data is separated into lines
    while(getline(rawData, line)){
        line = Trim(line);
        if(line.empty() || line[0] == '#') continue;
        //The data is separated into attributes
        stringstream rawline(line);
        string token;
        Command cmd;
        rawline >> cmd.name;
        while(getline(rawline, token, '-')){
            token = Trim(token);
            if(token.empty()) continue;
            //Flags
            if(token == "r"){
                cmd.params["r"] = "r";
                continue;
            }
            //The attributes and values are separated
            size_t pos = token.find('=');
            if(pos == string::npos) continue; //The simbol '=' is not found, the token es rejected
            string key = Trim(token.substr(0, pos));
            string value = Trim(token.substr(pos +1));
            if(key.empty() || value.empty()) continue; //not valid attribute
            
            if(value.front() == '"') value.erase(0, 1);
            if(value.back() == '"') value.pop_back();
            //saving attributes
            cmd.params[key] = value;
        }
        commands.push_back(cmd);
    }
    return commands;
}

vector<CommandResult> executeCommands(vector<Command>& commands){
    vector<CommandResult> results;
    for(const auto& currentCommand: commands){

        results.push_back({false, "[Error] The command '" + currentCommand.name + "' was not recognized"});
    }
    return results;
}

void RoutesReader::Reader(httplib::Server& api){
    api.Post("/execute", [](const httplib::Request& req, httplib::Response& res){
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");

        try{
            json body = json::parse(req.body);
            string data = body["data"];

            vector<Command> commands = splitCommands(data);
            vector<CommandResult> results = executeCommands(commands);

            json response;

            for(const CommandResult& currentResult: results){
                response["results"].push_back({
                    {"succes", currentResult.success},
                    {"message", currentResult.message}
                });
            }
            res.status = 200;
            res.set_content(response.dump(4), "application/json");
        } catch (const exception& e){
            json error;
            error["error"] = e.what();
            res.status = 400;
            res.set_content(error.dump(), "application/json");
        }
    });
}