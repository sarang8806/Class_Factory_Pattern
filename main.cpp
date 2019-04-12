#include <iostream>
#include <map>
#include <memory>

using namespace std;

//for storing the contact details 
map<long int, pair<string, string>> Information; 

//Main Base Class
class AddressBook
{
    public:        
        virtual void Display() const = 0;
        virtual void ContactFunctions() = 0;        
        virtual ~AddressBook() {}
};

// Add Contacts
class AddContact : public AddressBook
{
    private:
        long int phone_number;
        string name;
        string address;

    public:
        virtual void ContactFunctions() 
        {
            cout <<"Enter a Name: \n";
            cin >> name;
            cout <<"Enter a Phone Number: \n";
            cin >> phone_number;
            cout <<"Enter a Address: \n";
            cin >> address;            
            Information.insert(make_pair(phone_number, make_pair(name, address)));
        }
        
        virtual void Display() const
        {
            cout << "The contact details has been added" << "\n";
        }
        
        virtual ~AddContact() {}
};

// Delete Contacts
class DeleteContact : public AddressBook
{
    public:
		
 		void DeleteByName(string name)
		{
			map<long int, pair<string, string>>::iterator it ;
			if(!Information.empty())
			{
    			for(it = Information.begin(); it != Information.end(); ++it)
    			{
    				if(name == it->second.first)
    				{
    					Information.erase(it);
    					cout << name << " Deleted.\n";
    				}
    			}
			}
			else
			    cout <<"No contacts available\n";			        
		}
		
		void DeleteByPhoneNumber(long int phone_number)
		{
			map<long int, pair<string, string>>::iterator it ;
			if(!Information.empty())
			{
    			for(it = Information.begin(); it != Information.end(); ++it)
    			{
    				if(phone_number == it->first)
    				{
    					Information.erase(it);
    					cout << phone_number << " Deleted.\n";
    				}
    			}
			}
			else
			    cout <<"No contacts available\n";			        
		}
		
		virtual void ContactFunctions()
		{
			int choice = -1;
			long int phone_number;
			string name;

			while(choice != 0)
			{
				cout << "1. Delete by Name\n" << "2. Delete by Phone Number\n" << "0. Main Menu\n";
				cin >> choice;
				
				switch(choice)
				{
					case 1:
						cout << "Enter a name\n";
						cin >> name;	
						DeleteByName(name);
						break;
					case 2:
						cout << "Enter a phone number\n";
						cin >> phone_number;				
						DeleteByPhoneNumber(phone_number);
						break;
				}
			}			
		}
        virtual void Display() const
        {
			 cout << "The contact details has been deleted" << "\n";
		}
        
        virtual ~DeleteContact() {}
};

//Search Contact
class SearchContact : public AddressBook
{
	public:	
		void SearchByName(string name)
		{
		    if(!Information.empty())
		    {
    			for(auto &data : Information)
    			{
    				if(name == data.second.first)
    					cout <<"Phone\t\t:\t\t " << data.first << "\n" 
    					     <<"Name\t\t:\t\t"<< data.second.first << "\n"
                             <<"Address\t\t:\t\t"<< data.second.second <<"\n";
                }
		    }
		    else
		        cout <<"No contacts available\n";			        
		}
		
		void SearchByPhoneNumber(long int phone_number)
		{
		    if(!Information.empty())
		    {
    			for(auto &data : Information)
    			{
    				if(phone_number == data.first)
    					cout <<"Phone\t\t: " << data.first << "\n" 
    					     <<"Name\t\t: "<< data.second.first << "\n "
                             <<"Address\t\t: "<< data.second.second << '\n';
                }
		    }
		    else
		        cout <<"No contacts available\n";			        
		}
		
		virtual void ContactFunctions()
		{
			int choice = -1;
			long int phone_number;
			string name;

			while(choice != 0)
			{
				cout << "1. Search by Name\n" << "2. Search by Phone Number\n" << "0. Main Menu\n";
				cin >> choice;
				
				switch(choice)
				{
					case 1:
						cout << "Enter a name\n";
						cin >> name;	
						SearchByName(name);
						break;
					case 2:
						cout << "Enter a phone number\n";
						cin >> phone_number;				
						SearchByPhoneNumber(phone_number);
						break;
				}
			}
			
		}
		virtual void Display() const
        {}
		
		virtual ~SearchContact(){}
};

// Display Contacts
class DisplayContact : public AddressBook
{
    public:
        virtual void ContactFunctions()
        {
            if(!Information.empty())
            {
			    for(auto it =  Information.cbegin(); it !=  Information.cend(); ++it)
                    cout <<"Phone\t\t:\t\t"<< it->first << "\n" 
                         <<"Name\t\t:\t\t"<< it->second.first << "\n" 
                         <<"Address\t\t:\t\t"<< it->second.second << "\n\n\n";
            }
            else
                cout <<"No contacts available\n";            
		}

        virtual void Display() const
        {}
        
        virtual ~DisplayContact() {}
};

//Address book factory to call runtime
class AddressBookFactory
{
    public:
        enum AddressBookFunctionType
        {
            Add_Contact,
            Delete_Contact,
			Search_Contact,
            Display_Contact
        };
        
        static unique_ptr<AddressBook> PerformOperation(AddressBookFunctionType function_type)
        {
            switch(function_type)
            {
                case Add_Contact:
                    return make_unique<AddContact>();
                break;
                
                case Delete_Contact:
                    return make_unique<DeleteContact>();
                break;
				
                case Search_Contact:
                    return make_unique<SearchContact>();
                break;                
				
                case Display_Contact:
                    return make_unique<DisplayContact>();
                break;
            }
        }
};

//Global function 
void AddressBookFunctionality(AddressBookFactory::AddressBookFunctionType function_type)
{
    unique_ptr<AddressBook> address_book = AddressBookFactory::PerformOperation(function_type);
    address_book->ContactFunctions();
    address_book->Display();    
}

int main()
{
    int choice = -1;
    
    while(choice != 0)
    {
        cout <<"***********************CONTACT BOOK & ADDRESS***************************\n";
        cout << "Please Enter your choice" <<"\n";
        cout << "1. Add Contact" <<"\n" ;
        cout << "2. Delete Contact" <<"\n" ;
		cout << "3. Search Contact" <<"\n" ;
        cout << "4. Display Contact" <<"\n" ;
        cout << "0. Exit" <<"\n" ;
        cout << "***********************************************************************\n";
        cin  >> choice;
        
        switch(choice)
        {
                
            case 1:
                AddressBookFunctionality(AddressBookFactory::Add_Contact);
                break;
                
            case 2:
                AddressBookFunctionality(AddressBookFactory::Delete_Contact);
                break;
				
			case 3:
                AddressBookFunctionality(AddressBookFactory::Search_Contact);
                break;
				
            case 4:
                AddressBookFunctionality(AddressBookFactory::Display_Contact);
                break;
            
            case 0:
                cout << "Thank You!" << "\n";
                break;
                
            default:
                cout << "Please Enter Valid Option" << "\n";
                break;
        }
    }
    return 0;
}

