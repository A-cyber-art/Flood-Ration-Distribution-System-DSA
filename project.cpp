#include <iostream>
#include <string>
using namespace std;

// Node  for linked list and BST

class victim {

public:
	string name;
	string cnic;
	int age;
	int priority;
	string location;
	victim* next;
	victim* left;
	victim* right;

	// constructor

	victim(string namee, string cnicc, int agee, int priorityy,string loc) {

		name = namee;
		cnic = cnicc;
		age = agee;
		priority = priorityy;
		left = nullptr;
		right = nullptr;
		location = loc;
	}

};

// Stack node for emergency cases

class urgentNode {

public:
	victim* data;
	urgentNode* next;

	urgentNode(victim* v) {
		data = v;
		next = nullptr;
	}

};

//  Queue node for ration packetss

class rationNode {

public:
	string packet;
	rationNode* next;

	// constructor

	rationNode(string packett) {

		packet = packett;
		next = nullptr;
	}

};

class deliveryNode {

public:
	string victimName;
	string location;
	deliveryNode* next;

	deliveryNode(string name,string loc) {

		victimName = name;
		location = loc;
		next = nullptr;
	}

};

class VolunteerAssignment {

public:
	string volunteerName;
	string victimCnic;
	string VictimName;
	string location;
	VolunteerAssignment* next;

	VolunteerAssignment(string vname, string cnic, string name, string loc) {

		volunteerName = vname;
		victimCnic = cnic;
		VictimName = name;
		location = loc;
		next = nullptr;
	}
};


victim* headList = nullptr;
victim* rootBst = nullptr;
urgentNode* urgentTop = nullptr;
rationNode* rationFront = nullptr;
rationNode* rationRear = nullptr;
deliveryNode* deliveryTop = nullptr;
VolunteerAssignment* volunteerHead = nullptr;

// To store data about victim

victim* createVictim(string name, string cnic, int age, int priority,string location) {

	victim* v = new victim(name, cnic, age, priority,location);

	return v;
}

// check for duplicate cnic

bool isDuplicateCnic(victim* root, string victimcCnic) {

	if (root == nullptr) {
		return false;
	}

	if (root->cnic == victimcCnic) {
		return true;
	}

	if (victimcCnic < root->cnic ) {

		bool foundInLeft= isDuplicateCnic(root->left, victimcCnic);
		return foundInLeft;
	}

	else
	{

		bool foundInRight=  isDuplicateCnic(root->right, victimcCnic);
		return foundInRight;
	}

}

// insert a victim into BST based on cnic

void insertBST(victim*& root, victim* v) {

	if (root == nullptr) {

		root = v;
		return;
	}

	if (v->cnic < root->cnic) {

		insertBST(root->left, v);
	}

	else
	{
		insertBST(root->right, v);
	}

}

// inset a victim at the end of linked list (headlist)

void insertLinkedList(victim* v) {

	if (headList == nullptr) {

		headList = v;
		return;
	}

		victim* temp = headList;

		while (temp->next != nullptr) {
			temp = temp->next;
		}

		temp->next = v;

}

void RegisterVictim(string name, string cnic, int age, int priority,string location) {

	if (isDuplicateCnic(rootBst, cnic)) {

		cout << "CNIC is already registered." << endl;
		return;
	}

	victim* bstVictim = createVictim(name, cnic, age, priority, location);
	victim* listVictim = createVictim(name, cnic, age, priority, location);

	insertBST(rootBst, bstVictim);
	insertLinkedList(listVictim);

	cout << "Victim registered successfully." << endl;
}

victim* searchVictimByCnic(victim* root, string victimCnic) {

	if (root == nullptr) {

		return nullptr;
	}

	if (root->cnic == victimCnic) {
		return root;
	}

	if (victimCnic < root->cnic) {

		return searchVictimByCnic(root->left, victimCnic);
	}

	else
	{
		return searchVictimByCnic(root->right, victimCnic);
	}

}

void DisplayAllVictims() {

	victim* temp = headList;

	if (headList == nullptr) {
		cout << "No Victim registered yet." << endl;
	}
	cout << "\n-------------------Registered Victims------------------\n";

	while (temp != nullptr) {
		cout << "-------------------------------------------------------\n";
		cout << "Name      : " << temp->name << endl;
		cout << "CNIC      : "<<temp->cnic << endl;
		cout << "Age       : " << temp->age << endl;
		cout << "Priority  : " << temp->priority << endl;
		cout << "-------------------------------------------------------\n";

		temp = temp->next;
	}
}

void addRationPacket(string packet) {

	rationNode* r = new rationNode(packet);

	if (rationFront == nullptr) {

		rationFront = r;
		rationRear = r;
	}
	else
	{
		rationRear->next = r;
		rationRear = r;
	}

	cout << "Ration packet added." << endl;

}
victim* deleteFromBST(victim* root, string cnic) {

	if (root == nullptr) {

		return nullptr;
	}

	if (cnic < root->cnic) {

		root->left = deleteFromBST(root->left, cnic);
	}
	else if (cnic > root->cnic) {

		root->right = deleteFromBST(root->right, cnic);
	}
	else
	{
		// case 1: node has no child

		if (root->left == nullptr) {

			victim* temp = root->right;
			delete root;
			return temp;
		}

		// case 2: node has no right child

		else if (root->right == nullptr) {

			victim* temp = root->left;
			delete root;
			return temp;
		}

		// case 3 : node has two childern

		// 1st step : find inorder successor (smallest node in right subtree)

		victim* succ = root->right;

		while (succ->left != nullptr) {
			succ = succ->left;
		}

		// 2nd step : copy successor's data into current node

		root->name = succ->name;
		root->cnic = succ->cnic;
		root->age = succ->age;
		root->priority = succ->priority;
		root->location = succ->location;

		// 3rd step : delete into inorder successor

		root->right = deleteFromBST(root->right, succ->cnic);

	}

	return root;
}


void procesUrgentrequest(victim* v) {

	urgentNode* node = new urgentNode(v);
	node->next = urgentTop;
	urgentTop = node;

	cout << "Urgent request added." << endl;
}

void handleUrgentRequest() {

	if (urgentTop == nullptr) {

		cout << "No urgent cases found." << endl;
		return;
	}

	cout << "Handling urgent cases:" << urgentTop->data->name << endl;

	urgentNode* temp = urgentTop;
	urgentTop = urgentTop->next;

	delete temp;
}

void FindHighestPriorityVictim(victim* root, victim*& highest) {

	if (root == nullptr) {
		return;
	}

	FindHighestPriorityVictim(root->left, highest);

	if (highest == nullptr || root->priority > highest->priority) {
		highest = root;
	}

	FindHighestPriorityVictim(root->right, highest);

}


void deleteVictimFromList(string cnic) {

	if (headList == nullptr) {

		return;
	}

	if (headList->cnic == cnic) {
		
		victim* temp = headList;
		headList = headList->next;
		delete temp;
		return;
	}

	victim* prev = headList;
	victim* curr = headList->next;

	while (curr != nullptr) {

		if (curr->cnic == cnic) {

			prev->next = curr->next;
			delete curr;
			return;
		}

		prev = curr;
		curr = curr->next;
	}
}

void DisplayRationStock() {

	int count = 0;

	rationNode* temp = rationFront;

	while (temp != nullptr) {

		count++;
		temp = temp->next;
	}

	cout << "Ration packets left:" << count << endl;

}

void assignVolunteer(string volunteerName, string victimCnic, string volunteerlocation) {

	victim* v = searchVictimByCnic(rootBst, victimCnic);

	if (v == nullptr) {

		cout << "Victim not found. cannot assign volunteer." << endl;
		return;
	}

	if (v->location != volunteerlocation) {
		cout << "Volunteer location does not match victim's location!" << endl;
		cout << "Victim is at location:" << v->location << endl;
		return;
	}

	VolunteerAssignment* newAssIgn = new VolunteerAssignment(volunteerName, victimCnic, v->name, v->location);

	newAssIgn->next = volunteerHead;
	volunteerHead = newAssIgn;

	cout << "Volunteer '" << volunteerName << "' assigned to deliver ration to victim: " << v->name
		<< " (CNIC: " << v->cnic << " ) at location: " << v->location << endl;

}

string findVounteerForVictim(string cnic) {

	VolunteerAssignment* temp = volunteerHead;

	while (temp != nullptr) {

		if (temp->victimCnic == cnic) {

			return temp->volunteerName;
		}

		temp = temp->next;
	}

	return "";
}
void pushDeliveryPath(string name, string location) {

	deliveryNode* node = new deliveryNode(name, location);
	node->next = deliveryTop;
	deliveryTop = node;

	cout << "Delivery location recorded: " << location << endl;
}

void Delivery_History() {

	if (deliveryTop == nullptr) {

		cout << "No delivery path found." << endl;
		return;
	}

	cout << "Delivery path (latest to earliest):" << endl;

	deliveryNode* temp = deliveryTop;

	while (temp != nullptr) {

		cout << "Victim:" << temp->victimName<<" , Location:" <<temp->location<< endl;
		temp = temp->next;
	}
}


void distrubuteRation() {

	if (rationFront == nullptr) {

		cout << "No ration packets are available." << endl;
		return;
	}

	victim* targetVictim = nullptr;

	if (urgentTop != nullptr) {
		targetVictim = urgentTop->data;

		urgentNode* tempUrgent = urgentTop;
		urgentTop = urgentTop->next;
		delete tempUrgent;

		cout << "Urgent case is being served first." << endl;

	}
	else
	{
		FindHighestPriorityVictim(rootBst, targetVictim);

		if (targetVictim == nullptr) {
			cout << "No victim found for distribution." << endl;
			return;
		}
		
	}

	string victinName = targetVictim->name;
	string victimCnic = targetVictim->cnic;
	string victimLocation = targetVictim->location;

	pushDeliveryPath(victinName, victimLocation);

	deleteVictimFromList(victimCnic);
	rootBst = deleteFromBST(rootBst, victimCnic);


	rationNode* temp = rationFront;
	string distributePacket = temp->packet;
	rationFront = rationFront->next;
	delete temp;

	if (rationFront == nullptr) {

		rationRear = nullptr;
	}

	string volunteerName = findVounteerForVictim(victimCnic);

	if (volunteerName != "") {

		cout << "Ration Packet '" << distributePacket << "' delivered by Volunteer '" << volunteerName
			<< "' to Victim " << victinName << " (CNIC: " << victimCnic << " )" << endl;
	}
	else
	{
		cout << "Ration Packet '" << distributePacket << "' delivered to victim " << victinName
		<<	" (CNIC: " << victimCnic << " ) [ No volunteer assigned]" << endl;

	}
}

void deleteVolunteerAssignment(string cnic) {

	VolunteerAssignment* curr = volunteerHead;
	VolunteerAssignment* prev = nullptr;

	while (curr!=nullptr) {

		if (curr->victimCnic == cnic) {

			if (prev == nullptr) {
				volunteerHead = curr->next;
			}
			else {
				prev->next = curr->next;
			}

			delete curr;
			return;
		}

		prev = curr;
		curr = curr->next;
	}

}

// Desctructor
void deleteVictimList() {

	while (headList != nullptr) {

		victim* temp = headList;
		headList = headList->next;
		delete temp;
	}
}

void deleteBST(victim*root) {

	if (root == nullptr) {

		deleteBST(root->left);
		deleteBST(root->right);

		delete root;
	}
}

void delteRationQueue() {

	while (rationFront != nullptr) {

		rationNode* temp = rationFront;
		rationFront = rationFront->next;
		delete temp;
	}
}

void deleteUrgentStack() {

	while (urgentTop != nullptr) {

		urgentNode* temp = urgentTop;
		urgentTop = urgentTop->next;
		delete temp;
	}
}

void deleteDeliveryStack() {

	while (deliveryTop != nullptr) {

		deliveryNode* temp = deliveryTop;
		deliveryTop = deliveryTop->next;
		delete temp;
	}
}

void deleteVolunteerList() {

	while (volunteerHead != nullptr) {

		VolunteerAssignment* temp = volunteerHead;
		volunteerHead = volunteerHead->next;
		delete temp;
	}
}
int main() {

	int choice = 0;
	string name, cnic, packet,location;
	int age = 0;
	int priority = 0;

	do {
		cout << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "                                    SMART RATION DISTRIBUTION SYSTEM FOR FLOOD VICTIMS" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "1. Register New Victim" << endl;
		cout << "2. Search Victim by CNIC" << endl;
		cout << "3. Display All Registered Victims" << endl;
		cout << "4. Add Ration Packet" << endl;
		cout << "5. Distribute Ration Packet" << endl;
		cout << "6. Find highest Priority Victim" << endl;
		cout << "7. Process Urgent Request" << endl;
		cout << "8. Handle Urgent Request" << endl;
		cout << "9. Delete Victim by CNIC" << endl;
		cout << "10.Display Ration Stock" << endl;
		cout << "11.Assign Volunteer to Victim" << endl;
		cout << "12.Delivery History" << endl;
		cout << "0. Exit" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			cin.ignore();
			cout << "Enter Victim Name: ";
			getline(cin,name);
			cout << "Enter CNIC: ";
			getline(cin, cnic);
			cout << "Enter Age (1-100) : ";
			cin >> age;

			while (age <= 0 || age > 100) {
				cout << "Invalid Age Enter. Please Enter Age Between (1-100)." << endl;
				cout << "Enter Age Again:";
				cin >> age;
			}

			cout << "Enter Priority (1-10): ";
			cin >> priority;
			while (priority <= 0 || priority > 10) {
				cout << "Invalid priority Enter. Please Enter priority Between (1-10)." << endl;
				cout << "Enter priority Again:";
				cin >> priority;
			}

			cin.ignore();
			cout << "Enter Location:";
			getline(cin,location);
			RegisterVictim(name, cnic, age, priority,location);
			break;

		case 2: {
			cin.ignore();
			cout << "Enter CNIC to Search: ";
			getline(cin, cnic);

			victim* v = searchVictimByCnic(rootBst, cnic);
			if (v != nullptr) {

				cout << "Victim Found. " << endl << endl;
				cout << "Details:" << endl;
				cout<<"|Name:" << v->name << " | Age:" << v->age << " | Priority: " << v->priority <<"|" <<endl;

			}
			else
			{
				cout << "Victim not Found." << endl;
			}
			break;
		}
			
		case 3:
			DisplayAllVictims();
			break;

		case 4:
			cin.ignore();

			cout << "Enter Ration Packet Name: ";
			getline(cin,packet);
			addRationPacket(packet);
			break;

		case 5:
			cin.ignore();
			distrubuteRation();
			break;

		case 6:
		{
			victim* highest = nullptr;
			FindHighestPriorityVictim(rootBst, highest);
			if (highest != nullptr) {
				cout << "Highest Priority Victim: " << highest->name << " | Priority: " << highest->priority << endl;
			}
			else
			{
				cout << "No Victims registered yet." << endl;
			}
			break;
		}
		case 7:
			cin.ignore();

			cout << "Enter CNIC for urgent case: ";
			{
				getline(cin, cnic);

				victim* urgent = searchVictimByCnic(rootBst, cnic);

				if (urgent != nullptr) {

					procesUrgentrequest(urgent);
				}
				else
				{
					cout << "Victim not found." << endl;
				}
				break;
			}
		case 8:
			handleUrgentRequest();
			break;

		case 9: {
			cin.ignore();

			cout << "Enter CNIC to Delete: ";
			getline(cin, cnic);

			victim* found = searchVictimByCnic(rootBst, cnic);
			if (found != nullptr) {

				rootBst = deleteFromBST(rootBst, cnic);
				deleteVictimFromList(cnic);
				deleteVolunteerAssignment(cnic);
				cout << "Victim deleted." << endl;
			}
			else
			{
				cout << "Victim not found." << endl;
			}
			break;
		}

		case 10:
			DisplayRationStock();
			break;

		case 11:
			cin.ignore();

			cout << "Enter Volunteer Name: ";
			getline(cin, name);
			cout << "Enter victim CNIC: ";
			getline(cin, cnic);
			cout << "Enter delivery location:";
			getline(cin, location);
			assignVolunteer(name, cnic,location);
			break;

		case 12:
			Delivery_History();
			break;

		case 0:
			cout << "Exiting.Thank you!" << endl;
			break;

		default:

			cout << "Invalid choice! Please try again." << endl;
		}


	} while (choice != 0);

	deleteVictimList();
	deleteBST(rootBst);
	delteRationQueue();
	deleteUrgentStack();
	deleteDeliveryStack();
	deleteVolunteerList();

	return 0;

}

