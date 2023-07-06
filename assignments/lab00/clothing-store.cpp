/* COMP15 Spring 2023 Lab 0
 * The COMP15 Clothing Store
 * January 20, 2023
 * Name: Dan Vaccaro (dvacca01)
 */

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

struct ClothingItem {
	string item_type;
	int num_in_stock;
};

const string FILENAME = "inventory.txt";

int read_inventory(ClothingItem *&inventory, string input_file);
void find_in_array(string input, ClothingItem *inventory, int num_items);

int main() {
	cout << "Welcome to the COMP15 Clothing Store!" << endl;
	
	ClothingItem *inventory = NULL;
	int num_items = read_inventory(inventory, FILENAME);
	string input = "";
	
	while (input != "quit") {
		cout << "What would you like to buy?" << endl;
		cin >> input;
		find_in_array(input, inventory, num_items);
	}	
	
    
    // Did you allocate memory on the heap? Remember to free it up before
    // your program terminates!	
	delete [] inventory;
	return 0;
}

/* Function: read_inventory
 * Parameters: ClothingItem *inventory (passed by reference), and 
 *      the name of the file from which to read inventory data.
 * Returns: the number of different items currently in stock
 * Does: Allocates an array of ClothingItem objects on the heap
 *      and populates the array with data from the file */
int read_inventory(ClothingItem *&inventory, string input_file) {

    // 1. Open the input file and check that it opened successfully
	ifstream infile(input_file);
	if (infile.fail()) {
		cerr << "Error opening file." << endl;
		exit(EXIT_FAILURE);
	}

    // 2. Read the number of items from the file	
	int num_items;
	infile >> num_items;
    // 3. Allocate an array of that many ClothingItems on the heap, 
    //      and make sure inventory points to the beginning of that array
	ClothingItem *items_in_file = new ClothingItem[num_items];
	inventory = items_in_file;

    // 4. Read data from the file into the inventory array
	for (int i = 0; i < num_items; ++i) {
		//read item type
		infile >> inventory[i].item_type;
		//loop through item_type string to convert from upper case to lower
		for (int j = 0; j < (int)inventory[i].item_type.length(); j++) {
			if (inventory[i].item_type[j] >= 'A' && inventory[i].item_type[j] <= 'Z'){
				inventory[i].item_type[j] = inventory[i].item_type[j] + 32;
			}
		}
		//read number in stock
		infile >> inventory[i].num_in_stock;
	}

    // 5. Return the number of different items
	return num_items;
}

/* Function: find_in_array
 * Parameters: string representing the name of the clothing item to find,
 *      pointer to the beginning of the array of ClothingItems, and the
 *      number of items in the array.
 * Returns: void
 * Does: Searches the array for the given clothing item name. If found, 
 *      print the number of that item currently in stock. TODO: If not found, 
 *      tell the user we don't have any in stock. */
void find_in_array(string input, ClothingItem *inventory, int num_items) {
	if (input == "quit")
		return;
	//convert upper case to lower case
	for (int i = 0; i < (int)input.length(); i++) {
		if (input[i] >= 'A' && input[i] <= 'Z'){
			input[i] = input[i] + 32;
		}
	}
	//keep track of whether a match has been found
	bool found_check = false;
	//loop through inventory trying to match input to an item in inventory
	for (int i = 0; i < num_items; i++) {
		if (inventory[i].item_type == input) {
			found_check = true;
			cout << "We have " << inventory[i].num_in_stock 
                             << " " << inventory[i].item_type << endl;
		}
	}
	//if nothing was found, let the user know.
	if (!found_check) {
		cout << "Sorry! We don't have any " << input << "." << endl;
	}
}
