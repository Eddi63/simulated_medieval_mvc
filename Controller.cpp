//
// Created by Eden Akiva on 07/11/2022.
//

#include "Controller.h"
#include "Model.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

enum string_command {

    eExit,

    //view commands:
    eDefault,
    eSize,
    eZoom,
    ePan,
    eShow,

    //model commands
    eStatus,
    eGo,
    eCreate,

    eMaybeName,

    //after legal name commands:
    eCourse,
    ePosition,
    eDestination,
    eStop,
    eAttack,
    eStartWrk
};

string_command enum_f_str_cmd(std::string const& inString) {
    if (inString.compare("default") == 0) return eDefault;
    if (inString.compare("size") == 0) return eSize;
    if (inString.compare("zoom") == 0) return eZoom;
    if (inString.compare("pan") == 0) return ePan;
    if (inString.compare("show") == 0) return eShow;

    if (inString.compare("status") == 0) return eStatus;
    if (inString.compare("go") == 0) return eGo;
    if (inString.compare("create") == 0) return eCreate;

    if (inString.compare("course") == 0) return eCourse;
    if (inString.compare("position") == 0) return ePosition;
    if (inString.compare("destination") == 0) return eDestination;
    if (inString.compare("stop") == 0) return eStop;
    if (inString.compare("attack") == 0) return eAttack;

    if (inString.compare("startwork") == 0) return eStartWrk;


    if (inString.compare("exit") == 0) return eExit;

    return eMaybeName;
}

Controller::Controller() {

    view_ptr = Model::GetInstance()->return_View_ptr(); //std::make_shared<View>();


}

Controller::~Controller() {

}

// creates View object, runs the program by accepting user commands, then destroys View object
void Controller::run(int argc, char* argv[]) { //char** argv
    if(!load_castles()){
        std::cerr << "problem loading castles" << std::endl;
        return;
    }

    if(!load_farms()){
        std::cerr << "problem loading farms" << std::endl;
        return;
    }
    bool keep_going = true;
    while(keep_going) {
        std::cout << "Time " << Model::GetInstance()->getTime() << ": Enter command: ";
        std::string command_line;
        getline(std::cin, command_line);
        std::vector<std::string> command_vec = tokenize(command_line, ' ');
        if(command_vec.empty()){
            std::cerr << "enter is not a command" << std::endl;
            continue;
        }
        std::string first_word = command_vec[0];
        bool maybe_name = true;
        switch (enum_f_str_cmd(first_word)) {
            case eExit:
                maybe_name = false;
                if (command_vec.size() == 1) {
                    std::cout << "Game Over" << std::endl;
                    return;
                } else {
                    std::cerr << "bad exit command try again" << std::endl;
                }
                break;
///////////////////////////////////// FOR VIEW
            case eDefault:
                maybe_name = false;
                if (command_vec.size() == 1) {
                    dfault();
                } else {
                    std::cerr << "bad default command try again" << std::endl << std::endl;
                }
                break;

            case eSize:
                maybe_name = false;
                if (command_vec.size() == 2 && is_int(command_vec[1])) {
                    size(std::stoi(command_vec[1]));
                } else {
                    std::cerr << "ERROR: Expected an integer for size command." << std::endl << std::endl;
                }
                break;
            case eZoom:
                maybe_name = false;
                if (command_vec.size() == 2 && isFloat(command_vec[1])) {
                    zoom(std::stof(command_vec[1]));
                } else {
                    std::cerr << "ERROR: Expected an double for zoom command." << std::endl << std::endl;
                }
                break;

            case ePan:
                maybe_name = false;
                if (command_vec.size() == 3 && isFloat(command_vec[1]) && isFloat(command_vec[2])) {
                    pan(std::stof(command_vec[1]), std::stof(command_vec[2]));
                } else {
                    std::cerr << "bad pan command try again" << std::endl;
                }
                break;
            case eShow:
                maybe_name = false;
                if (command_vec.size() == 1) {
                    show();
                } else {
                    std::cerr << "bad show command try again" << std::endl;
                }
                break;
///////////////////////////////////// FOR MODEL
            case eStatus:
                maybe_name = false;
                if (command_vec.size() == 1) {
                    status();
                } else {
                    std::cerr << "bad status command try again" << std::endl;
                }
                break;

            case eGo:
                maybe_name = false;
                if (command_vec.size() == 1) {
                    go();
                } else {
                    std::cerr << "bad go command try again" << std::endl;
                }
                break;

            case eCreate:
                maybe_name = false;
                if (command_vec.size() == 4) { //knight
                    create(command_vec[1], command_vec[2], command_vec[3]);
                } else if (command_vec.size() == 5) { //p or t
                    float x, y;
                    try {
                        x = x_from_stream(command_vec[3]);
                        y = y_from_command(command_vec[4]);
                        create(command_vec[1], command_vec[2], x, y);
                    }
                    catch (const std::invalid_argument &ia) {
                        std::cerr << "Invalid argument: float not found" << ia.what() << std::endl;
                        std::cerr << "create line error" << std::endl;
                    }

                } else {
                    std::cerr << "bad create command try again" << std::endl;
                }
                break;

            default:
                //std::cerr << "command might be agent name" << std::endl;
                break;

        }
///////////////////////////////////// FOR AFTER AGENT NAME
        if (maybe_name) {
            if (Model::GetInstance()->is_an_agent_name(command_vec[0])) {
                std::string second_word = command_vec[1];
                switch (enum_f_str_cmd(second_word)) {
                    case eStop:
                        if (command_vec.size() == 2) {
                            Model::GetInstance()->stop_agent(command_vec[0]);
                        } else {
                            std::cerr << "bad stop agent command try again" << std::endl;
                        }
                        break;
                    case eAttack:
                        if (command_vec.size() == 3) {
                            if (Model::GetInstance()->is_a_thug_name(command_vec[0]) &&
                                Model::GetInstance()->is_a_peasant_name(command_vec[2])) {
                                Model::GetInstance()->t_attack(command_vec[0], command_vec[2]);
                            }
                        } else {
                            std::cerr << "bad attack agent command try again" << std::endl;
                        }
                        break;

                    case eCourse:
                        if (command_vec.size() == 3 &&
                            Model::GetInstance()->is_a_knight_name(command_vec[0])) { //knight
                            if (isFloat(command_vec[2])) {
                                Model::GetInstance()->get_knight_on_course(command_vec[0], stof(command_vec[2]));
                            } else {
                                std::cerr << " bad angle given" << std::endl;
                            }
                        } else if (command_vec.size() == 4 && Model::GetInstance()->is_a_thug_name(command_vec[0])) {
                            if (isFloat(command_vec[2]) && is_int(command_vec[3])) {
                                Model::GetInstance()->get_thug_on_course(command_vec[0], stof(command_vec[2]),
                                                                         stoi(command_vec[3]));
                            } else {
                                std::cerr << "bad angle or speed given" << std::endl;
                            }
                        } else {
                            std::cerr << "bad course agent command try again" << std::endl;
                        }
                        break;

                    case ePosition:
                        if (command_vec.size() > 3 && command_vec.size() < 6) { //4 or 5 arguments
                            float x, y;
                            try {
                                x = x_from_stream(command_vec[2]);
                                y = y_from_command(command_vec[3]);
                            }
                            catch (const std::invalid_argument &ia) {
                                std::cerr << "Invalid loc argument: float not found" << ia.what() << std::endl;
                                std::cerr << "agent position error" << std::endl;
                                break;
                            }
                            if (command_vec.size() == 4 && Model::GetInstance()->is_a_knight_name(command_vec[0])) { //knight
                                try{
                                    Model::GetInstance()->give_M_knight_cref_by_name(command_vec[0])->position(Loc(x, y));
                                }
                                catch(const std::invalid_argument &ia) {
                                    std::cerr << "knight not found in position call" << ia.what() << std::endl;
                                    break;
                                }
                            } else if (command_vec.size() == 5 && Model::GetInstance()->is_a_thug_name(command_vec[0])) {
                                if (is_int(command_vec[3])) {
                                    try {
                                        Model::GetInstance()->give_M_thug_cref_by_name(command_vec[0])->position(
                                                Loc(x, y), stoi(command_vec[4]));
                                    }
                                    catch (const std::invalid_argument &ia) {
                                        std::cerr << "Invalid loc argument: thug not found" << ia.what()
                                                  << std::endl;
                                        break;
                                    }
                                } else {
                                    std::cerr << "bad speed given" << std::endl;
                                }
                            } else {
                                std::cerr << "bad position agent command try again" << std::endl;
                            }
                        } else {
                            std::cerr << "wrong amount of arguments for agent position command, try again" << std::endl;
                        }
                        break;

                    case eDestination:
                        if (command_vec.size() == 3) {
                            if (Model::GetInstance()->is_a_knight_name(command_vec[0]) &&
                                Model::GetInstance()->is_a_site_name(command_vec[2])) {
                                try {
                                    std::shared_ptr<Site> site_ptr = Model::GetInstance()->give_M_site_cref_by_name(
                                            command_vec[2]);
                                    Model::GetInstance()->give_M_knight_cref_by_name(command_vec[0])->destination(
                                            site_ptr);
                                }
                                catch (const std::invalid_argument &ia) {
                                    std::cerr << "Invalid loc argument: site not found" << ia.what() << std::endl;
                                    std::cerr << "destination not given site name" << std::endl;
                                    break;
                                }
                                break;
                            }
                        } else {
                            std::cerr << "bad destination agent command try again" << std::endl;
                        }
                        break;
                    case eStartWrk:
                        if (command_vec.size() == 4) {
                            if (Model::GetInstance()->is_a_peasant_name(command_vec[0]) &&
                                Model::GetInstance()->is_a_site_name(command_vec[2]) &&
                                Model::GetInstance()->is_a_site_name(command_vec[3])){
                                try {
                                    std::shared_ptr<Site> farm_ptr = Model::GetInstance()->give_M_site_cref_by_name(
                                            command_vec[2]);
                                    std::shared_ptr<Site> castle_ptr = Model::GetInstance()->give_M_site_cref_by_name(
                                            command_vec[3]);
                                    if(farm_ptr->is_a_farm() && !castle_ptr->is_a_farm()){

                                        Model::GetInstance()->give_M_peasant_cref_by_name(command_vec[0])->start_working(std::dynamic_pointer_cast<Farm>(farm_ptr),
                                                                                                                         std::dynamic_pointer_cast<Castle>(castle_ptr));

                                    }
                                }
                                catch (const std::invalid_argument &ia) {
                                    std::cerr << "Invalid loc argument: site not found" << ia.what() << std::endl;
                                    std::cerr << "destination not given site name" << std::endl;
                                    break;
                                }
                                break;
                            }
                        } else {
                            std::cerr << "bad startwork agent command try again" << std::endl;
                        }
                        break;


                    default:
                        std::cerr << "second agent command completely inaccurate" << std::endl;
                        break; //is this right? do i need it?

                }
            } else {
                std::cerr << "bad agent name command try again" << std::endl;
            }
        }
    }
}


bool Controller::load_castles(){
    std::ifstream f1("castles.dat");
    if (!f1) {
        std::cout << "Error: could not find castles data " << std::endl;
        return false;
    }
    std::string castle_line_data;
    std::string castleName, x_etc, y_etc, inven_str;
    float x, y;
    //int inventory_;
    //double x, y;
    for( std::string line; getline( f1, line ); )
    {
        std::vector<std::string> str_vec_of_line = mystrtok(line, ' ');
        if(str_vec_of_line.size()!=4){
            std::cerr << "Error: castle line of wrong length " << std::endl;
            return false;
        }
        castleName = str_vec_of_line[0];
        x_etc = str_vec_of_line[1];
        y_etc = str_vec_of_line[2];
        inven_str = str_vec_of_line[3];
        try {
            x = x_from_stream(x_etc);
            y = y_from_stream(y_etc);
        }
        catch (const std::invalid_argument &ia) {
            std::cerr << "Invalid argument: float not found" << ia.what() << std::endl;
            std::cerr << "castle line incorrect" << std::endl;
            return false;
        }
        if(castleName[castleName.length()-1] != ','){
            std::cerr << "Invalid argument: castleName dont have commas farm line incorrect" << std::endl;
            return false;
        }
        else{
            castleName = castleName.substr(0, castleName.length()-1);
        }
        if (! is_int(inven_str) ){
            std::cerr << "Invalid argument: inventory int not found, castle line incorrect" << std::endl;
            return false;
        }

        Loc a(x,y);

        std::shared_ptr<Castle> my_new_castle = std::make_shared<Castle>(std::move(castleName), a, std::stoi(inven_str));
        //std::shared_ptr<Castle> my_new_castle(new Castle(std::move(c_name), Loc(x,y), inventory));
        //Site_list.push_back(my_new_castle);
        Model::GetInstance()->addCastle(std::move(my_new_castle));

    }
//    while (!f1.eof()) { // keep reading until end-of-file
//        //check if line is in the correct format and add the port accordingly
//
//    }
    //close file
    f1.close();
    return true;
}

bool Controller::load_farms() {
    std::ifstream f2("farms.dat");
    if (!f2) {
        std::cout << "Error: could not find farms data " << std::endl;
        return false;
    }
    std::string farm_line_data;
    std::string farmName, x_etc, y_etc, inven_str, farm_strength_str;
    float x, y;
    int inventory_, farm_str;
    //double x, y;
    for (std::string line; getline(f2, line);) {
        std::vector<std::string> str_vec_of_line = mystrtok(line, ' ');
        if (str_vec_of_line.size() != 5) {
            std::cerr << "Error: farm line of wrong length " << std::endl;
            return false;
        }
        farmName = str_vec_of_line[0];
        x_etc = str_vec_of_line[1];
        y_etc = str_vec_of_line[2];
        inven_str = str_vec_of_line[3];
        farm_strength_str = str_vec_of_line[4];
        try {
            x = x_from_stream(x_etc);
            y = y_from_stream(y_etc);
        }
        catch (const std::invalid_argument &ia) {
            std::cerr << "Invalid argument: float not found" << ia.what() << std::endl;
            std::cerr << "farm line incorrect" << std::endl;
            return false;
        }
        if(farmName[farmName.length()-1] != ',' || inven_str[inven_str.length()-1] != ',' ){
            std::cerr << "Invalid argument: farmname or strength dont have commas farm line incorrect" << std::endl;
            return false;
        }
        else{
            farmName = farmName.substr(0, farmName.length()-1);
            inven_str = inven_str.substr(0,inven_str.length()-1);
        }
        if (! is_int(inven_str) || ! is_int(farm_strength_str)){
            std::cerr << "Invalid argument: inventory or farmstrength int not found, farm line incorrect" << std::endl;
            return false;
        }
        Loc a(x, y);
        std::shared_ptr<Farm> my_new_farm = std::make_shared<Farm>(std::move(farmName), a, stoi(inven_str), stoi(farm_strength_str));

        Model::GetInstance()->addFarm(std::move(my_new_farm));
    }
    //close file
    f2.close();
    return true;
}

std::vector<std::string> Controller::mystrtok(std::string str, char delim){
    std::vector<std::string> tokens;
    std::string temp = "";
    for(int i = 0; i < str.length(); i++){
        if(str[i] == delim){
            tokens.push_back(temp);
            temp = "";
        }
        else
            temp += str[i];
    }
    tokens.push_back(temp);
    return tokens;
}

float Controller::x_from_stream(std::string x_input) const{
    // (20.00,
    float num_float;
    if (x_input[0] == '(' && x_input[x_input.length()-1] == ',' && isFloat(x_input.substr(1, x_input.length()-2))) {
        num_float = std::stof( x_input.substr(1, x_input.length()-2) );
        return num_float;
    }
    else{
        throw std::invalid_argument("input not in proper x float format");
    }
    //return num_float;
}

float Controller::y_from_stream(std::string y_input) const{
    // 10.00),
    float num_float;
    if (y_input[y_input.length()-2] == ')' && y_input[y_input.length()-1] == ',' && isFloat(y_input.substr(0, y_input.length()-2))) {
        num_float = std::stof( y_input.substr(0, y_input.length()-2) );
        return num_float;
    }
    else{
        throw std::invalid_argument("input not in proper y float format");
    }
    //return num_float;
}

float Controller::y_from_command(std::string y_input) const{ //no comma
    // 10.00)
    float num_float;
    if (y_input[y_input.length()-1] == ')' && isFloat(y_input.substr(0, y_input.length()-1))) {
        num_float = std::stof( y_input.substr(0, y_input.length()-1) );
        return num_float;
    }
    else{
        throw std::invalid_argument("input not in proper y float format");
    }
    //return num_float;
}

bool Controller::is_int(std::string string_potential) const{
    for (int i = 0; i < string_potential.length(); i++) {
        if( !isdigit(string_potential[i]))
            return false;
    }
    return true;
};

#include <sstream>

bool Controller::isFloat( std::string myString ) const{
    std::istringstream iss(myString);
    float f;
    iss >> f;
    // Check the entire string was consumed and if either failbit or badbit is set

    //bool ans = iss.eof() && !iss.fail();
    //iss.clear();
    return iss.eof() && !iss.fail(); //ans;
}

//commands to view:
void Controller::dfault() {
    Model::GetInstance()->return_View_ptr()->clear();
}
void Controller::size(unsigned int s) {
    if( s < 7){
        std::cerr << "ERROR: New map size is too small." << std::endl;
        return;
    }
    if( s > 30){
        std::cerr << "ERROR: New map size is too big." << std::endl;
        return;
    }
    Model::GetInstance()->return_View_ptr()->set_disp_size(s);
}
void Controller::zoom(float z) {
    if( z < 0){
        std::cerr << "ERROR: New map scale must be positive." << std::endl;
        return;
    }
    Model::GetInstance()->return_View_ptr()->set_scale(z);
}
void Controller::pan(float x, float y) {
    Model::GetInstance()->return_View_ptr()->set_origin(Loc(x,y));
}
void Controller::show() {
    Model::GetInstance()->return_View_ptr()->draw();
}


//commands to model:

void Controller::status() const {
    Model::GetInstance()->status();
}

void Controller::go() {
    Model::GetInstance()->update();
}

void Controller::create(std::string given_a_name, std::string type_P_or_T, float coord_x, float coord_y) {
    if ( Model::GetInstance()->is_an_agent_name(given_a_name) ) {
        std::cerr << "Name already an agent name, try again" << std::endl;
        return;
    }
    if( type_P_or_T.compare("Peasant") == 0 ) {
        std::shared_ptr<Peasant> p;
        try {
            //Peasant p(p_name, p_loc);
            p = std::make_shared<Peasant>(std::move(given_a_name),
                                          Loc(coord_x, coord_y)); //could i create a loc in here and move it?
            Model::GetInstance()->addPeasant(std::move(p));
            return;
        } catch (const std::exception &e) { //why const, why & ?
            std::cerr << e.what() << std::endl;
            return;
        } catch (...) {
            std::cerr << "Unknown exception creating obj" << std::endl;
            return;
        }
    }
    else if( type_P_or_T.compare("Thug") == 0 ){
        std::shared_ptr<Thug> t;
        try {
            //Peasant p(p_name, p_loc);
            t = std::make_shared<Thug>(std::move(given_a_name),
                                          Loc(coord_x, coord_y)); //could i create a loc in here and move it?
            Model::GetInstance()->addThug(std::move(t));
            return;
        } catch (const std::exception &e) { //why const, why & ?
            std::cerr << e.what() << std::endl;
            return;
        } catch (...) {
            std::cerr << "Unknown exception creating obj" << std::endl;
            return;
        }
    }
    else{
        std::cerr << "Unknown agent type, try again" << std::endl;
    }
}

void Controller::create(std::string given_a_name, std::string type_Knight, std::string given_site_name) {
    if ( Model::GetInstance()->is_an_agent_name(given_a_name) ) {
        std::cerr << "Name already an agent name, try again" << std::endl;
        return;
    }
    if (! Model::GetInstance()->is_a_site_name(given_site_name) ) {
        std::cerr << "Site doesnt exist, try again" << std::endl;
        return;
    }

    if( type_Knight.compare("Knight") == 0 ) {
        std::shared_ptr<Knight> k;
        try {
            //Peasant p(p_name, p_loc);
            k = std::make_shared<Knight>(std::move(given_a_name), Model::GetInstance()->give_M_site_cref_by_name(given_site_name) );
            Model::GetInstance()->addKnight(std::move(k));
            return;
        } catch (const std::exception &e) { //why const, why & ?
            std::cerr << e.what() << std::endl;
            return;
        } catch (...) {
            std::cerr << "Unknown exception creating obj" << std::endl;
            return;
        }
    }
    else{
        std::cerr << "Type not Knight, try again" << std::endl;
    }
}

std::vector<std::string> Controller::tokenize(const std::string& line, char del){
    std::vector<std::string> tokens;
    std::stringstream check1(line);
    std::string temp;
    while (getline(check1, temp, del)) {
        tokens.push_back(temp);
    }
    return tokens;
}



