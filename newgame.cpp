#include <iostream>
#include <string>
#include <vector>
using namespace std;

class object {
	public:
		object(string nm, string cont){
			name = nm;
			content = cont;
		}
		
		void look(){
			cout << content << endl;
		}
		string getName() {
			return name;
		}
	private:
		string name;
		string content;		
};

class location {
	public: 
		location(string location){
			name = location;
		}
		
		location(string location, object item, string descr) {
			name = location;
			items = {item};
			description = descr;
		}

		//look() prints out both the description of the location
		//and the description for each item in the room stored in "items".
		void look() {
			cout << description << endl;
			if(!items.empty()){
				for(object item : items){
					item.look();
				}
			}
		}

		void go(string noun);

		vector<object> items;
		
	private:
		string name;
		string description;
		
};


void setting();
void inpFilter(string input);
void direction(string noun);
void get(string item);
void drop(string item);
void look();
void objLook(string noun);
void helper(vector<object>& source, vector<object>& destination, string noun);

object quarters = {"quarters", "You see the stack of quarters. They are very shiny."};
object wallet = {"wallet", "You see your wallet. It looks empty."};
object keys = {"keys", "You see your keys. Wow you own a lambo?"};

location bar = {"bar", quarters, "You are in the bar. There is a dj playing and the lights are dim, strobe lights are flashing."};
location deli = {"deli", wallet, "You are in the deli. It is full of people and dark."};
location arcade = {"arcade", keys, "You are in the arcade. People are playing pool."};

vector<location> room = {bar, deli, arcade};
vector<object> inventory = {};
int current_room = 0;

vector<string> stopwords = {"the ", "with ", "on ", "in "};

int main(){
	setting();

	cout  << "You are facing the bar and have a stack of quarters next to you." << endl
		  << "You seem to have lost your keys and wallet. You should probably look for those." << endl
		  << "If you want to move use left, right, forward, backward." << endl;
	
	string input = "";

	//removes stopwords if found in user input 
	while(getline(cin, input)){

		inpFilter(input);		

		string verb = input.substr(0, input.find(" "));
		string noun = input.substr(input.rfind(" ") + 1, input.length());
		
	
		
		if(verb == noun) {
			noun = "";  
		}
		
		//pipes inventory into separate look function outside of classes
		if(verb == "inventory"){
			look();
		}
		else if(verb == "look" && noun == ""){
			room.at(current_room).look();
		}
		else if(verb == "look"){
			objLook(noun);
		}
		else if(verb == "go"){
			direction(noun);
		}
		else if(verb == "get"){
			get(noun);
		}
		else if(verb == "drop"){
			drop(noun);
		}
		else if(verb == "quit"){
			break;
		}
		else {
			cout << "That doesn't sound very fun sorry." << endl;
		}
	}
}

//States the setting 
void setting(){
	cout << "You are in downtown Fullerton at Heroes Bar and Grill." << endl
		 << "There is a dj playing and the lights are dim but strobe lights are flashing." << endl;	
}

void inpFilter(string input){
	for(int i = 0; i < stopwords.size(); ++i)
	{
		int pos = input.find(stopwords.at(i));
		while(pos != -1) 
		{
			input.erase(pos, stopwords.at(i).length());
			pos = input.find(stopwords.at(i));
		}	
	}	
}
//Deletes object from source that matches noun, and adds to destination
//
void helper(vector<object>& source, vector<object>& destination, string noun){
	for(int i = 0; i < source.size(); ++i){
		if(source.at(i).getName() == noun){
			destination.push_back(source.at(i));
			source.erase(source.begin() + i);
			--i;
			cout << "remaining items: ";
			for(object item: source) cout << item.getName() << " ";
			cout << endl;
		}
		else {
			cout << "I don't see that anywhere." << endl;
		}
	}
}

//Pipes noun into helper and deletes object from location adds to inventory 
//
void get(string noun) {
	if(current_room == 0){
		helper(room.at(0).items, inventory, noun);
	}
	else if(current_room == 1) {
		helper(room.at(1).items, inventory, noun);
	}
	else if(current_room == 2){
		helper(room.at(2).items, inventory, noun);
	}
}
//Pipes noun into helper and deletes object from inventory adds to location
//	
void drop(string noun){
	if(current_room == 0){
		helper(inventory, room.at(0).items, noun);
	}
	else if(current_room == 1){
		helper(inventory, room.at(1).items, noun);
	}
	else if(current_room == 2){
		helper(inventory, room.at(2).items, noun);
	}
}

//Prints items in inventory
void look() {
		if(!inventory.empty()){
			cout << "You have the following in your pockets:\n";
			for(object item : inventory){
				cout << "- " << item.getName() << "* " << endl;	
			}
		}
		else {
			cout <<  "You have nothing in your pockets." << endl;
		}
	}
	
void objLook(string noun){
	for(object item : room.at(current_room).items){
		if(item.getName() == noun){
			item.look();
		}
		else{
			cout << "I don't see that anywhere." << endl;
		}
	}
	for(object item : inventory){
		if(item.getName() == noun){
			item.look();
		}
		else{
			cout << "I don't see that anywhere." << endl;
		}
	}
}

//Calls location::go() to print movement based on current_room location
void direction(string noun){
	if(current_room >= 0 && current_room < room.size()){
		room.at(current_room).go(noun);
	}
}

//Prints output of room you enter and changes current_room variable
void location::go(string input) {
	if(current_room == 0){
		if(input == "left"){
			current_room = 1;
			cout << "You walk into the deli. It is full of people and dark." << endl;
		}
		else if(input == "right"){
			current_room = 2;
			cout << "You walk into the arcade. People are playing pool." << endl;
		}
		else if(input == "forward"){
			cout << "You're blocked, go a different way." << endl;
		}
		else if(input == "backward"){
			cout << "You're in the crowd now, but still at the bar." << endl;
		}
	}
	else if(current_room == 1){
		if(input == "left" || input == "right"){
			cout << "You're blocked, go a different way." << endl;
		}
		else if(input == "forward"){
			cout << "You go toward the end of the hall and try the door, but it's locked." << endl;
		}
		else if(input == "backward"){
			current_room = 0;
			cout << "You go back into the bar, it's still smokey and strobe ligths are flashing." << endl;
		}
	}
	else if(current_room == 2){
		if(input == "left" || input == "right"){
			cout << "You're blocked, go a different way." << endl;
		}
		else if(input == "forward"){
			cout << "You go toward the end of the hall and try the door, but it's locked." << endl;
		}
		else if(input == "backward"){
			current_room = 0;
			cout << "You go back into the bar, it's still smoky and strobe lights are flashing." << endl;
		}
	}
}

