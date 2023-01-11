/* Controller
This class is responsible for controlling the Model and View according to interactions
with the user.
*/

//This is a single object whose responsibility is to manage the interaction with the user,
// and route the received inputs for the model.
//Also responsible for the management of errors in user inputs.
#include "View.h"

#include <memory>
#include <vector>

class Controller {

    std::shared_ptr<View> view_ptr;

public:	
	Controller();
	~Controller();


    void run(int argc, char* argv[]);
    bool load_castles();
    bool load_farms();
    float x_from_stream(std::string x_input) const;
    float y_from_stream(std::string x_input) const;
    bool is_int(std::string string_potential) const;
    bool isFloat( std::string myString ) const;
    std::vector<std::string> mystrtok(std::string str, char delim);

    float y_from_command(std::string y_input) const; //no comma


    //commands to view:
    void dfault(); // to replicate automatic parameters of map
    void size(unsigned int s); // 6<s<=30, s defines num of cols and rows
    void zoom(float z); // unsigned real number //relation of 1 km to cell in map
    void pan(float x, float y); //make origin of map
    void show(); // show current map

    //commands to model:
    void status() const; //all obj in simulation describe current state
    void go(); //to update all obj in discrete time unit of one hr

    void create(std::string given_a_name, std::string type_P_or_T, float coord_x, float coord_y); // to create new agent
    void create(std::string given_a_name, std::string type_Knight, std::string legal_site_name);// for

    //commands after agent name:
    void course(float angle_degree, int speed_if_thug);
    void course(float angle_degree); //if knight
    void position(int x, int y, int speed_if_thug);
    void position(int x, int y); //if knight?
    void destination(const std::string& site_name); // for knight
    void stop();
    void attack(const std::string& peasant_name);
    void startwork();


    std::vector<std::string> tokenize(const std::string& line, char del = ' ' );

};
