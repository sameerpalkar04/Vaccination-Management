// Header Files
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctype.h>
#include <limits>
#include <algorithm>
using namespace std;

// CLASS 1: USER DETAILS
class user_details 
{
    private:
    // Member variables
        string password;
    protected:
    // Member Variables
        string first_name;
        string last_name;
        string age;
        string gender;
        string blood_group;
        string contact_no;
        string no_ofdoses;
        string email;
        string city;
        string booked;
    public:
    // Member Functions
        
        void signup();
        void get_pwd();
        void confirm_pwd(string);
        void get_contactno();
        void get_no_ofdoses();
        void get_bloodgroup();
        void get_name();
        void split(string,char);
        void get_age();
        void get_gender();
        void get_email();
        void get_city();
        void delete1();

        // Function to set the password
        void set_password(string pswd)
        {
            password=pswd;
        }

        // Function to return the password
        string return_pass()  
        {
            return password;
        }
};

// CLASS 2: BOOKING - DERIVED CLASS OF USER_DETAILS
class booking : public user_details
{
    protected:
    // Member Variables
        string vaccine_name;
        string date;
        string slot;
        string centre_name;
    public:
    // Member Functions
        void user_login();
        void vaccine_booking();
        void get_date();
        void get_slot();
        void get_vaccinename();
        void input_bookingdata();
        void display(string, string, string, string);
        void display();
        void login_choice();
        // Constructor definintion
        booking()
        {
            booked="0"; // booked initialized as 0
        }
}book_obj; // Object for the class created

// CLASS 3: ADMIN
class admin
{
    private:
    // Member Variables
        string first_name;
        string last_name;
        string age;
        string gender;
        string blood_group;
        string contact_no;
        string no_of_doses;
        string email;
        string city;
        string password;
        string booking_status;
        string vaccine_name;
        string slot;
        string date;
        string center_name;

    // Member Functions
        void display_all();
        void search(string fname, string lname);
        void search(string gender);
        void search();
        void search(int booking_status);
        void delete_by_name();

    public:
        void admin_menu();
};

// Find Function
string find(string line,int num)
{
    int count = 0;
    string found;
    stringstream det;
    det<<line;
    while(count<num)
    {
        getline(det,found,',');
        count++;
    }
    return found;   
}

// Function to book an appointment for vaccination
void booking :: vaccine_booking() 
{
    booked="1";
    cout << "\n\n************************** BOOKING **************************\n";
    cout << "" << endl;
    int centre_choice;
    string line;
    ifstream hospitals;
    fstream outputf;
    hospitals.open("centrenames.csv"); // Fetching names of hospitals in various cities
    outputf.open("userdetails.csv",ios::out | ios::app );
    while(getline(hospitals,line))
    {
        // If the user's city is same as the city in centrenames.csv
        if(find(line,1) == city)
        {
            // Centre names in the user's city 
            cout << "CHOOSE YOUR CENTRE: -\n\n";
            cout<<"Enter 1. for: "<<find(line,2)<<endl;
            cout<<"Enter 2. for: "<<find(line,3)<<endl;
            cout<<"Enter 3. for: "<<find(line,4)<<endl;
            cout<<"Enter 4. for: "<<find(line,5)<<endl;
            cout << "" << endl;
            break;
        }
    }
    cout << "                      CHOOSE YOUR CENTRE                     " << endl;
    cout << "                     --------------------                    " << endl;
    cout << "" << endl;
    cout << "CENTRE: ";
    cin >> centre_choice;
    // If the user doesn't enter the correct choice
    if(centre_choice<1 || centre_choice>4) 
    {
        cout << "" <<  endl;
        cout << "Enter the correct choice (1,2,3 or 4)" << endl;
        vaccine_booking();
        return;
    }
    else // Correct choice entered 
    {
        centre_name = find(line,centre_choice+1);
        cout << "" << endl;
    }
    hospitals.close(); // File closed
    get_date(); // Date function called
    get_slot(); // Slot function called
    get_vaccinename(); // Vaccine name function called
}

// Function to delete the old data and enter the new data
void booking :: input_bookingdata() 
{
    fstream outputf;
    book_obj.delete1(); // Old data deleted
    outputf.open("userdetails.csv",ios::out | ios::app ); // File opened
    // Inserting new data
    outputf<<email<<","<<return_pass()<<","<<first_name<<","<<last_name<<","<<city<<","<<age<<","<<gender<<","<<
    blood_group<<","<<contact_no<<","<<no_ofdoses<<","<<booked<<","<<vaccine_name<<","<<slot<<","<<date<<","<<centre_name<<"\n";
    outputf.close();

    cout << endl << "" << endl;
    cout << "                BOOKING COMPLETED SUCCESSFULLY               " << endl;
    cout << "" << endl;
    display(vaccine_name,date,slot,centre_name); // COMPILE TIME POLYMORPHISM USED (FUNCTION OVERLOADING)     
}

// Function to get the date
void booking :: get_date()
{
    int d;
    int m;
    int y;
    cout << "                        CHOOSE THE DATE                      " << endl;
    cout << "                       -----------------                     " << endl;
    cout << "" << endl;
    cout<<"Enter the Date (DD/MM/YYYY) : ";

    cin >> d; // read the day
    if ( cin.get() != '/' ) // make sure there is a slash between DD and MM
    {
        get_date();
        return;
    }
    cin >> m; // read the month
    if ( cin.get() != '/' ) // make sure there is a slash between MM and YYYY
    {
        get_date();
        return;
    }
    cin >> y; // read the year

    int months_31[]={1,3,5,7,8,10,12};
    int months_30[]={4,6,9,11};
    bool exists_31 = find(months_31, months_31 + 7, m) != months_31 + 7;
    bool exists_30 = find(months_30, months_31 + 4, m) != months_31 + 4;

    // If the user enter wrong date for the month of February
    if(m==2 &&(!(d>=1 && d<=28)))
    {
        cout << endl << "" << endl;
        cout << "         ENTER THE CORRECT DATE (February has 28 days)\n       "<<endl;
        get_date();
        return;
    }
    // If the month is of 30 days but date entered is wrong
    else if(exists_30 &&(!(d>=1 && d<=30)))
    {
        cout << endl << "" << endl;
        cout << "                     ENTER THE CORRECT DATE\n                  "<<endl;
        get_date();
        return;
    }
    // If the month is of 31 days but date entered is wrong
    else if(exists_31 &&(!(d>=1 && d<=31)))
    {
        cout << endl << "" << endl;
        cout << "                     ENTER THE CORRECT DATE\n                  "<<endl;
        get_date();
        return;
    }
    // If the month entered by the user is invalid
    else if(!(exists_30 || exists_31 || m==2))
    {
        cout << endl << "" << endl;
        cout << "                     ENTER THE CORRECT DATE\n                  "<<endl;
        get_date();
        return;
    }
    // If the year entered is not 2023
    if(y!=2023)
    {
        cout << endl << "" << endl;
        cout << "                  SLOT CURRENTLY UNAVAILABLE\n                  "<<endl;
        get_date();
        return;
    }

    string dstring=to_string(d);
    string mstring=to_string(m);
    string ystring=to_string(y);
    // Date saving format
    date=dstring+"/"+mstring+"/"+ystring;
}

// Function to get the slot
void booking :: get_slot() 
{
    cout << endl << "" << endl;
    cout << "                        CHOOSE YOUR SLOT                     " << endl;
    cout << "                       ------------------                    " << endl;
    cout << "" << endl;
    string slots[5]={"9:00 - 10:00","10:30 - 11:30","12:00 - 13:00","16:00 - 17:00","17:30 - 18:30"};
    for(int i=0; i<5; i++) // SLOTS Displayed
    {
        cout<<i+1<<". "<<slots[i]<<endl;
    }

    int option;
    cout << "" << endl;
    cout<<"SLOT: ";
    cin>>option;
    if(option>=1 && option<=5)
    {
        slot=slots[option-1]; // value of slot saved in the member variable
    }
    else 
    {
        // If the user enters the wrong option
        cout << "" << endl;
        cout << "Enter the correct option" << endl;
        get_slot(); // Recursively calling the function
    }
}

// Function to get the vaccine mame
void booking :: get_vaccinename() 
{
    int choice;
    cout << "" << endl;
    cout << "                       CHOOSE THE VACCINE                    " << endl;
    cout << "                      --------------------                   " << endl;
    cout << "" << endl;
    cout << "Your age is " << age << " years old, the options available are: -\n\n";
    // If the user's age is below 18
    if(age<"18") 
    {
        cout << "";
        cout << "";
        cout << "1. Covaxin" << endl;
        vaccine_name = "Covaxin"; 
        /* Only one option is showed as according to govt regulations, people below 18
        can be administred with only COVAXIN*/
        cout << "";
    }
    // If the user's age is above 18
    else 
    {
        // User will be given an option to choose their vaccine
        cout << "";
        cout << "1. Covaxin    | Price: Rs 225/-" << endl;
        cout << "2. Covishield | Price: Rs 225/-" << endl;
        cout << "3. MODERNA    | Price: Rs 1500/-" << endl;
        cout << "4. Sputnik V  | Price: Rs 1200/-" << endl;
        cout << "" << endl;
        cout << "CHOICE: ";
        cin >> choice;
        // If the user enter the wrong choice
        if(choice<1 || choice >4) 
        {
            cout << "" << endl;
            cout << "Enter the correct choice";
            get_vaccinename();
        }
        // If the user enter the correct choice
        else 
        {
            if(choice == 1) 
            {
                vaccine_name = "Covaxin";
            }
            else if (choice == 2) 
            {
                vaccine_name = "Covishield";
            }
            else if (choice == 3) 
            {
                vaccine_name = "MODERNA";
            }
            else 
            {
                vaccine_name = "Sputnik V";
            }
        }
    }
    cout << "" << endl;
}

// LOGIN Function
void booking::user_login()
{
    string iemail, ipassword;
    int flag = 0;
    cout << "\n************************* USER LOGIN *************************\n";
    cout << "" << endl;
    cout<<"Enter your registered email-id: ";
    cin>>iemail;
    cout<<"Enter your password: ";
    cin>>ipassword;
    string line="";
    ifstream inputf;
    // Opening the file
    inputf.open("userdetails.csv"); 
    // Fetching line from the csv file
    while (getline(inputf,line))
    {
        string temp;

        stringstream inputstring(line);
        string pswd;
        getline(inputstring,email,',');
        getline(inputstring,pswd,',');
        set_password(pswd);
        // Checking if the email and password entered by the user is same as in the file
        if(email==iemail && pswd==ipassword)
        {
            // Fetching the data from the file
            flag =1;
            getline(inputstring,first_name,',');
            getline(inputstring,last_name,',');
            getline(inputstring,city,',');
            getline(inputstring,age,',');
            getline(inputstring,gender,',');
            getline(inputstring,blood_group,',');
            getline(inputstring,contact_no,',');
            getline(inputstring,no_ofdoses,',');
            getline(inputstring,booked,',');
            // If the user has made a booking then fetch the booking details as well
            if(booked=="1")
            {
                getline(inputstring,vaccine_name,',');
                getline(inputstring,slot,',');
                getline(inputstring,date,',');
                getline(inputstring,centre_name,',');
            }
            cout << endl;
            cout << "               YOU HAVE SUCCESSFULLY LOGGED IN              "<< endl;
            break;
        }
    }
    // If the account is not found i.e. wrong credentials are entered
    if (flag == 0)
    {
        cout << "" << endl;
        cout << "     YOUR ACCOUNT WAS NOT FOUND, ENTER THE DETAILS AGAIN     " << endl;
        cout << "" << endl;
        user_login(); // Recursively calling the function
        return;
    }
    inputf.close(); // File closed
}

// Function to get the city
void user_details::get_city()
{
    int city_choice;
    cout << "" << endl;
    cout<<"Choose your city from the following options: - "<<endl;
    cout<<"1. For Delhi"<<endl<<"2. For Mumbai"<<endl<<"3. For Bangalore"<<endl<<"4. For Chennai"<<endl<<"5. For Kolkata"<<endl;
    cout << "" << endl;
    cout << "CITY: ";
    cin>>city_choice;
    int arr[]={1,2,3,4,5};
    bool exists = find(arr, arr + 5, city_choice) != arr + 5;
    if(!exists)
    {
        cout << "" <<  endl;
        cout << "          ENTER A NUMBER CORRESPONDING TO YOUR CITY          " << endl;
        get_city(); // Recursively calling the function
        return;
    }
    else
    {
        // Assigning the city name
        if(city_choice==1) {city="Delhi";}
        if(city_choice==2) {city="Mumbai";}
        if(city_choice==3) {city="Bangalore";}
        if(city_choice==4) {city="Chennai";}
        if(city_choice==5) {city="Kolkata";}
    }
}

// Function to get the email ID
void user_details::get_email()
{
    cout << "" <<endl;
    cout<<"EMAIL ID: ";
    cin>>email;
    if((email.find("@") == string::npos) || (email.find(".") == string::npos))
    {
        cout << "" << endl;
        cout << "                    ENTER A VALID EMAIL-ID                   " << endl;
        get_email(); // Recursively calling the function
        return;
    }

    // Checking if the user is entering the same email as already present
    string line="";
    ifstream inputf;
    inputf.open("userdetails.csv");
    while (getline(inputf,line))
    {
        string temp;

        stringstream inputstring(line);

        getline(inputstring,temp,',');
        if(email==temp)
        {
            cout << "" << endl;
            cout << "          A USER WITH THIS EMAIL-ID ALREADY EXISTS           "<<endl;
            cout << "" << endl;
            get_email();
            return;
        }
    }
}

// Function to get the gender
void user_details::get_gender()
{
    cout<<"Enter your gender (male / female / other): -"<<endl;
    cout << "GENDER: ";
    cin>>gender;

    string arr[]={"male","female","other"};
    // Checking if the user enters some other gender
    if ((gender!="male") && (gender!="female") && (gender!="other"))
    {
        cout << "" <<  endl;
        cout << "           ENTER GENDER FROM THE GIVEN OPTIONS ONLY          "<<endl;
        cout << "" << endl;
        get_gender(); // Recursively calling the function
        return;
    }
}

// Function to get the age
void user_details::get_age()
{
    int flag=0;
    cout<<"AGE: ";
    cin>>age;
    // Checking if the age entered is in thousands, coz no-one lives for that many years
    if(age.length()>3)
    {
        cout << "" << endl;
        cout << "                    ENTER THE CORRECT AGE                    " << endl;
        cout << "" << endl;
        get_age(); // Recursively calling the function
        return;
    }
    // If the age entered has any character apart from digit
    for(int i=0 ;i<age.length();i++)
    {
        if (!isdigit(age[i]))
        {
            flag=1;
        }
    }
    if(flag!=0) // Checking if flag is not equal to zero, ie if it has some error
    {
        cout << "" <<  endl;
        cout << "                    ENTER THE CORRECT AGE                    " << endl;
        cout << "" << endl;
        get_age(); // Recursively calling the function
        return;
    }
}

// Function to split the name
void user_details:: split (string str, char seperator)
{  
    string strings[2];
    int currIndex = 0, i = 0;  
    int startIndex = 0, endIndex = 0;  
    while (i <= str.length())  
    {
        // If the seperator is encountered or i is equal to the length of the string
        if (str[i] == seperator || i == str.length())  
        {  
            endIndex = i;  
            string subStr = "";  
            subStr.append(str, startIndex, endIndex - startIndex);  
            strings[currIndex] = subStr;  
            currIndex += 1;  
            startIndex = endIndex + 1;  
        }  
        i++;  
    }
    first_name=strings[0];
    last_name=strings[1];
}  

// Function to get the name from the user
void user_details::get_name()
{
    string name;
    cout<<"NAME: ";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    getline(cin,name);
    split(name,' '); // Calling the split function
}

// Function to get the blood group
void user_details :: get_bloodgroup() 
{
    string blood_group1;
    int i,len,flag=0;
    cout << "" << endl;
    cout << "Enter your blood group from the given options: -" << endl;
    cout << "" << endl;
    cout << "A+\tA-\tB+\tB-\tAB+\tAB-\tO+\tO-" << endl;;
    cout << "" << endl;
    cout << "BLOOD GROUP: ";
    cin >> blood_group1;
    len = blood_group1.length();
    cout << "" <<endl;

    // If it matches with the list then it's assigned to the member variable
    if(blood_group1=="A+" || blood_group1=="A-" || blood_group1=="B+" || blood_group1=="B-" || blood_group1=="AB+" || blood_group1=="AB-" || blood_group1=="O+" || blood_group1=="O-") 
    {
        blood_group = blood_group1;
    }
    // If it doesn't have a digit but does not match with the list then the user has to enter again
    else 
    {
        cout<<""<<endl;
        cout << "                  ENTER A VALID BLOOD GROUP                  " << endl;
        get_bloodgroup(); // Recursively calling the function
        return;
    }
}

// Function to get the number of doses
void user_details :: get_no_ofdoses() 
{
    string no_ofdoses1;
    cout << "\nNo of doses already taken: -\n0. For zero doses\n1. For one dose\n2. For two doses\n3. For booster dose\n\n";
    cout << "NO. OF DOSES: ";
    cin >> no_ofdoses1;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    // To check if the no of doses entered by the user is 0,1,2,3 only.
    if(no_ofdoses1 == "0" || no_ofdoses1 == "1" || no_ofdoses1 == "2" || no_ofdoses1 == "3") 
    {
        cout << "" << endl;
        no_ofdoses = no_ofdoses1;
    }
    else 
    {
        cout << "" << endl;
        cout << "                   ENTER THE CORRECT OPTION                  " << endl;
        get_no_ofdoses(); // Recursively calling the function
        return;
    }
}

// Function to get the contact number
void user_details :: get_contactno() {
    int i;
    int flag=0;
    cout << "CONTACT NUMBER: ";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cin >> contact_no;
     
    int len = contact_no.length();
    if(len!=10) 
    {
        // Checking if the contact has less than 10 digits in it
        cout << "" << endl;
        cout << "               ENTER A 10 DIGIT CONTACT NUMBER               " << endl;
        cout << "" << endl;
        get_contactno(); // Recursively calling the function
        return;
    }
    for(i=0;i<len;i++) 
    {
        // Checking whether the contact has any alphabets
        if(!isdigit(contact_no[i])) 
        {
            flag=1;
        }
    }
    if(flag==1)
    {
        cout << "-------------------------------------------------------------" << endl;
        cout << "" << endl;
        cout << "                 ENTER A VALID CONTACT NUMBER                " << endl;
        cout << "" << endl;
        get_contactno(); // Recursively calling the function
        return;
    }
   
}

// Function to confirm the password made by the user
void user_details :: confirm_pwd(string pass_wrd) 
{
    string password1;
    cout << "" << endl;
    cout << "Re-enter the password to confirm" << endl;
    cout << "CONFIRM PASSWORD: "; 
    cin >> password1; // Re-entering the password
    if(password1==pass_wrd) // Checking if the password matches
    {
        cout << "" << endl;
        cout << "                     SIGNUP SUCCESSFUL                       " << endl;
        this->password = pass_wrd; // Assinging the value of member varible password
        cout << "-------------------------------------------------------------" << endl;
        cout << "" << endl;
    }
    else 
    {
        cout << "" << endl;
        cout << "           WRONG PASSWORD ENTERED, TRY AGAIN                 " << endl;

        confirm_pwd(pass_wrd); // Recursively calling the function
    }
}

// Function to get the password
void user_details :: get_pwd() 
{
    string password;
    cout << "PASSWORD: ";
    cin >> password;
    if(password.length() <8) // Checking if the password is strong or not
    {
        cout << "" << endl;
        cout << "      ENTER A STRONGER PASSWORD (8 CHARACTERS ATLEAST)       " << endl; 
        cout << "" << endl;
        get_pwd(); // Recursively calling the function
    }
    else 
    {
        cout << "" << endl;
        confirm_pwd(password);  // Calling the function to confirm the password
    }
}

// NEW USER / SIGNUP Function
void user_details :: signup() 
{
    fstream outputf;
    outputf.open("userdetails.csv",ios::out | ios::app );
    cout << "\n********************* SIGNUP/ NEW USER **********************\n";
    cout << "" << endl;
    cout << "                     Enter your details                        " << endl;
    cout << "" << endl;
    get_name(); // CALL: Function to get the name
    get_age(); // CALL: Function to get the blood group
    cout << "" << endl;
    get_gender(); // CALL: Function to get the gender
    get_bloodgroup(); // CALL: Function to get the blood group
    get_contactno(); // CALL: Function to get the contact number
    get_email(); // CALL: Function to get the email
    get_city(); // CALL: Function to get the city
    get_no_ofdoses(); // CALL: Function to get the number of doses already taken
    cout << "";
    cout << "Create a strong password, atleast of 8 characters" << endl;
    get_pwd(); // CALL: Function to get the password
    outputf<< email<<","<<password<<","<<first_name<<","<<last_name<<","<<city<<","<<age<<","<<gender<<","<<blood_group<<","<<contact_no<<","<<no_ofdoses<<","<<booked<<"\n";
    outputf.close(); // File closed
}

// User Choice Function, To Book an appointment or to exit 
void booking :: login_choice()
{
    int cho1;
    // If the user has made a booking then the booking option won't be displayed
    if(booked=="1")
    {
        display(vaccine_name,date,slot,centre_name); 
        cout<<"Enter Your Choice: -\n\n1. To Delete Account Details\n2. Change Booking Details\n3. Exit\n\n";
        cout << "CHOICE: "; // Entering the choice
        cin>>cho1;
        if(cho1==1)
        {
            string check="N";
            cout<<"ARE YOU SURE YOU WANT TO DELETE YOUR ACCOUNT? (Y/N): ";
            cin>>check;
            if(check=="Y")
            {
                book_obj.delete1();
                cout << "                ACCOUNT DELETED SUCCESSFULLY               " << endl<<endl;
                return;
            }
            else
            {
                cout << "                    DELETE TERMINATED                        "<<endl;
            }

        }
        else if(cho1==2)
        {
            vaccine_booking();
            input_bookingdata();
            cout << "============================================================="<<endl<<endl;
            cout << "                          THANK YOU                          "<<endl<<endl;
            cout << "============================================================="<<endl<<endl;
            exit(0);
        }
        else if(cho1==3)
        {
            cout << "============================================================="<<endl<<endl;
            cout<<  "                     SUCCESSFULLY EXITED                     "<<endl<<endl;
            cout << "============================================================="<<endl<<endl;
            exit(0);
        }
        // Wrong choice entered
        else
        {
            cout<<"\nPlease Enter a Valid Input(1,2 or 3)\n\n";
            login_choice();
            return;
        }

    // If no booking has been made by the user
    }
    else {
        // If the user is not fully vaccinated
        if(no_ofdoses!="3")
        {
            cout<<"Enter Your Choice: -\n\n1. To Book an Appointment\n2. To Delete Account Details\n3. Exit\n\n";
            cout << "CHOICE: ";
            cin>>cho1;
            if(cho1==1)
            {
                vaccine_booking();
                input_bookingdata();
                cout << "============================================================="<<endl<<endl;
                cout << "                          THANK YOU                          "<<endl<<endl;
                cout << "============================================================="<<endl<<endl;
                exit(0);
            }
            else if(cho1==2)
            {
                string check="N";
                cout<<"ARE YOU SURE YOU WANT TO DELETE YOUR ACCOUNT? (Y/N): ";
                cin>>check;
                if(check=="Y")
                {
                book_obj.delete1();
                cout<<"                ACCOUNT DELETED SUCCESSFULLY                     " << endl<<endl;
                return;
                }
                else
                {
                    cout<<"DELETION TERMINATED"<<endl;
                    login_choice();
                    return;
                }
            }
            else if(cho1==3)
            {
                cout << "============================================================="<<endl<<endl;
                cout<<  "                     SUCCESSFULLY EXITED                     "<<endl<<endl;
                cout << "============================================================="<<endl<<endl;
                exit(0);
            }
            // Wrong choice entered by the user
            else
            {
                cout<<"\nPlease Enter a Valid Input(1,2 or 3)\n\n";
                login_choice();
                return;
            }
        }
        // If the user is fully vaccinated
        else;
        {
            cout<<"Enter Your Choice: -\n\n1. To Delete Account Details\n2. Exit\n\n";
            cout << "CHOICE: ";
            cin>>cho1;
            if(cho1==1)
            {
                string check="N";
                cout<<"ARE YOU SURE YOU WANT TO DELETE YOUR ACCOUNT? (Y/N): ";
                cin>>check;
                if(check=="Y")
                {
                book_obj.delete1();
                cout<<"                ACCOUNT DELETED SUCCESSFULLY                     " <<endl<<endl;
                return;
                }
                else
                {
                    cout<<"DELETION TERMINATED"<<endl;
                    login_choice();
                    return;
                }
            }
            else if(cho1==2)
            {
                cout << "============================================================="<<endl<<endl;
                cout<<  "                     SUCCESSFULLY EXITED                     "<<endl<<endl;
                cout << "============================================================="<<endl<<endl;
                exit(0);
            }
            // Wrong choice entered by the user
            else
            {
                cout<<"\nPlease Enter a Valid Input(1,2 or 3)\n\n";
                login_choice();
                return;
            }
        }
    }
}

// Display Details Function
void booking::display()
{
    // Displaying the details to the user
            cout<<endl<<"User details are as follows: "<<endl;
            cout<<endl<<"Name: "<<first_name<<" "<<last_name<<endl;
            cout<<"Age: "<<age<<endl;
            cout<<"Gender: "<<gender<<endl;
            cout<<"Blood Group: "<<blood_group<<endl;
            cout<<"City: "<<city<<endl;
            cout<<"Email-id: "<<email<<endl;
            cout<<"Contact Number: "<<contact_no<<endl;

            // If the user is fully vaccinated 
            if (no_ofdoses=="3")
            {
                cout << "" << endl;
                cout << "-------------------------------------------------------------" << endl;
                cout << endl << "         CONGRATULATIONS!!! YOU ARE FULLY VACCINATED         "<<endl;
                cout << "" << endl;
                cout << "-------------------------------------------------------------" << endl;
                cout << "" << endl;
            }
            // If the user has taken 2 vaccines
            else if(no_ofdoses=="2")
            {
                cout << "-------------------------------------------------------------" << endl;
                cout << endl << "      YOU HAVE TAKEN "<<no_ofdoses<<" DOSES OF THE CORONAVIRUS VACCINE       "<<endl;
                cout << "" << endl;
                cout << "-------------------------------------------------------------" << endl;
                cout << "" << endl;
            }
            // If the user has taken 1 vaccine
            else if(no_ofdoses=="1")
            {
                cout << "-------------------------------------------------------------" << endl;
                cout << endl << "      YOU HAVE TAKEN "<<no_ofdoses<<" DOSE OF THE CORONAVIRUS VACCINE       "<<endl;
                cout << "" << endl;
                cout << "-------------------------------------------------------------" << endl;
                cout << "" << endl;
            } 
            // If the user has taken no vaccine
            else {
                cout << "-------------------------------------------------------------" << endl;
                cout << endl << "       YOU HAVE TAKEN NO DOSE OF THE CORONAVIRUS VACCINE     "<<endl;
                cout << "" << endl;
                cout << "-------------------------------------------------------------" << endl;
                cout << "" << endl;
            }
}

// Function to display the details after booking - POLYMORPHISM IS USED
void booking::display(string v1, string d1, string s1, string c1) // Same function name, new parameters added
{
    cout << "*************************************************************" << endl;
    cout << "" << endl;
    cout << "                 BOOKING DETAILS FOR "<<first_name<<endl<<endl;
    cout << "" << endl;
    cout << "Name: "<<first_name<<" "<<last_name<<endl;
    cout << "Age: "<<age<<endl;
    cout << "Gender: "<<gender<<endl;
    cout << "Appointment Status: Scheduled with Dose "<<stoi(no_ofdoses)+1<<endl;
    cout << "Vaccine Choice: "<<v1<<endl;
    cout << "Booked Date: "<<d1<<endl;
    cout << "Booked Slot: "<<s1<<endl;
    cout << "Booked Centre Name: "<<c1<<endl; 
    cout << "" << endl;
    cout << "*************************************************************" << endl;

}

// Function to find the details
string find1(string line,int num)
{
    int count = 0;
    string found;
    stringstream det;
    det<<line;
    while(count<num)
    {
        getline(det,found,',');
        count++;
    }
    return found;
}

// Function to delete the data from .csv file
void user_details::delete1()
{
    string confirm="N";

    ifstream details;
        details.open("userdetails.csv");
        string line;

        ofstream temp;
        temp.open("temp.csv");

        while(getline(details, line))
        {
            if (find1(line,1) != email)
            {
            temp<<line<<endl;
            }
        }
        temp.close(); // Temp file closed
        details.close(); // Original file closed
        remove("userdetails.csv"); // Original file deleted
        rename("temp.csv","userdetails.csv"); // Temp file renamed
        cout << "" << endl;
}

// Function to login as the admin
void admin_login()
{
    string entered_username, entered_password, username,password;
    static int count_num_tries = 3;

    if(count_num_tries==3)
    {
        cout<<""<<endl;
        cout << "************************ ADMIN LOGIN ************************"<<endl<<endl;
    }
    ifstream admin_cred;
    admin_cred.open("admin_credentials.txt");
    admin_cred>>username;
    admin_cred>>password;
    admin_cred.close();
    cout<<"Please Enter Username: ";
    cin>>entered_username;
    cout<<"Please Enter Password: ";
    cin>>entered_password;
    // If the credentials match, then the admin is logged in
    if(username == entered_username && password == entered_password)
    {
        cout << endl << "                         WELCOME                             "<<endl;
        cout << "              YOU HAVE SUCCESSFULLY LOGGED IN                "<<endl;
        cout << "-------------------------------------------------------------" << endl;
        cout<<""<<endl;
        cout<<"Opening Admin Menu ........... "<<endl<<endl;

        admin obj; // Object created for the admin class
        obj.admin_menu(); // Function call

    }
    // If the admin enters wrong credentials
    else
    {
        // Tries are decremented
        count_num_tries--;
        cout << "" << endl;
        cout << "                     INVALID CREDENTIALS                     " << endl;
        if(count_num_tries >0)
        {
            cout << "                   You have "<<count_num_tries<<" more attempt                " <<endl;
            cout << "-------------------------------------------------------------" << endl;
            admin_login();
        }
        // If number of tries exceed 3
        else
        {
            cout << "" << endl;
            cout << "             SORRY, YOU ARE OUT OF ATTEMPTS                   " << endl;
            cout << "                EXITING FROM THE PROGRAM                     "<<endl<<endl;
            exit(0);
        }  
    } 
}

// Admin Menu Function
void admin::admin_menu()
{
    int int_choice = 0;
    while(int_choice != 7)
    {
        int int_choice;
        string choice;
        cout << "-------------------------------------------------------------" << endl;
        cout << "                         ADMIN MENU                          "<<endl;
        cout << "-------------------------------------------------------------" << endl << endl;
        cout<<"ENTER 1 TO DISPLAY DETAILS OF ALL THE USERS."<<endl;
        cout<<"ENTER 2 TO SEARCH USER BY NAME."<<endl;
        cout<<"ENTER 3 TO SEARCH USER BY GENDER."<<endl;
        cout<<"ENTER 4 TO SEARCH USER BY CITY."<<endl;
        cout<<"ENTER 5 TO SEARCH USER BY BOOKING STATUS."<<endl;
        cout<<"ENTER 6 TO DELETE ACCOUNT."<<endl;
        cout<<"ENTER 7 TO EXIT."<<endl<<endl;
        cout << "-------------------------------------------------------------" << endl << endl;
        cout<<"Kindly Enter Your choice: ";
        cin>>choice;
        for(int i=0;i<choice.length();i++)
        {
            // If the choice entered is not a digit
            if(!isdigit(choice[i]))
            {
                cout<<""<<endl;
                cout << "                    ENTER A VALID CHOICE                     " << endl;
                cout<<"\n"<<endl;
                admin_menu(); // Recusively calling the function
                return;
            }
        }
        int_choice=stoi(choice);
        // Switch cases
        switch(int_choice)
        {
            // TO DISPLAY DETAILS OF ALL THE USERS 
            case 1:
            {
                display_all(); // Function Call
                break;
            }
            // TO SEARCH USER BY NAME
            case 2:
            {
                cout << "" << endl;
                string fname,lname;
                cout<< "Enter First Name: ";
                cin>>fname;
                cout<< "Enter Last Name: ";
                cin>>lname;

                search(fname,lname); // POLYMORPHISM USED - FUNCTION OVERLOADING, New arguments passed
                break;
            }
            // TO SEARCH USER BY GENDER
            case 3:
            {
                string gender;
                cout << "" << endl;
                cout << "Enter Gender from the Following Options (male/female/other)" << endl;
                cout << "Gender: ";
                cin>>gender;
                
                search(gender); // POLYMORPHISM USED - FUNCTION OVERLOADING, New arguments passed
                break;
            }
            // TO SEARCH USER BY CITY
            case 4:
            {
                search(); // Function Call
                break;
            }
            // TO SEARCH USER BY BOOKING STATUS
            case 5:
            {
                int flag = 0;
                while(flag == 0)
                {
                    int choice;
                    cout << "" << endl;
                    cout<<"Enter 1: To Find All Users With Booking Status : Booked"<<endl;
                    cout<<"Enter 0: To Find All Users With Booking Status : Not Booked"<<endl << endl;
                    cout<<"Enter Your Choice: ";
                    cin>>choice;
                    if(choice == 1 || choice == 0)
                    {
                        search(choice); // Function call
                        flag = 1;
                    }
                    // If the choice entered by the admin is wrong
                    else
                    {
                        cout << "" << endl;
                        cout << "                    ENTER A VALID CHOICE                     " << endl;
                    }
                }
                break;
            } 
            // TO DELETE ACCOUNT
            case 6:
            {
                delete_by_name(); // Function call
                break;
            }
            // TO EXIT
            case 7:
            {
                cout << "============================================================="<<endl<<endl;
                cout<<  "                     SUCCESSFULLY EXITED                     "<<endl<<endl;
                cout << "============================================================="<<endl<<endl;
                exit(0);
            }
            // Default case
            default:
            {
                cout << "                    ENTER A VALID CHOICE                     " << endl;
                cout << "\n\n";
                admin_menu(); // Recursively calling the function
            }
        }
    }
}

// Function to display the details of all the users
void admin::display_all()
{
    ifstream details;
    details.open("userdetails.csv"); // File opened

    string line;
    int i = 1;

    cout << endl << "            DISPLAYING THE DETAILS OF ALL USERS              "<<endl;
    cout << "============================================================="<<endl<<endl<<endl;
    getline(details,line);
    while(getline(details,line))
    {
        cout<<"DETAILS OF USER "<<i<<" ARE: "<<endl<<""<<endl;
        stringstream data(line);
        // data<<line;
        getline(data,email,',');
        getline(data,password,',');
        getline(data,first_name,',');
        getline(data,last_name,',');
        getline(data,city,',');
        getline(data,age,',');
        getline(data,gender,',');
        getline(data,blood_group,',');
        getline(data,contact_no,',');
        getline(data,no_of_doses,',');

        cout<<"Name: "<<first_name<<" "<<last_name<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"Gender: "<<gender<<endl;
        cout<<"Blood Group: "<<blood_group<<endl;
        cout<<"City: "<<city<<endl;
        cout<<"Email-id: "<<email<<endl;
        cout<<"Contact Number: "<<contact_no<<endl;
        cout<<"No of doses: "<<no_of_doses<<endl<<endl;       
        
        getline(data,booking_status,',');

        // If the user has made a booking then booking details are also showed
        if(booking_status ==  "1")
        {
            getline(data,vaccine_name,',');
            getline(data,slot,',');
            getline(data,date,',');
            getline(data,center_name,',');

            cout<<"The User has Booked an Appointment: "<<endl<<endl;
            cout<<"Vaccine Name: "<<vaccine_name<<endl;
            cout<<"Slot: "<<slot<<endl;
            cout<<"Date: "<<date<<endl;
            cout<<"Center Name: "<<center_name<<endl;
        }
        // If no booking has been made
        else
        {
            cout<<"No Appointment Booked."<<endl;
        }
        cout << "" << endl;
        cout << "-------------------------------------------------------------" << endl << endl;
        i++;
        
    }
    details.close(); // File closed
    cout << "        DETAILS OF ALL THE USERS HAVE BEEN DISPLAYED         "<<endl<<endl;
    cout << "              GOING BACK TO ADMIN MENU ......                "<<endl << endl;
}

// Function to search the user by their name
void admin::search(string fname, string lname)
{
    string line;
    int flag = 0;
    
    ifstream check;
    check.open("userdetails.csv");

    while(getline(check,line))
    {
        // If the first name and the last name entered by the user matches
        if(find(line,3) == fname && find(line,4)== lname)
        {
            flag++;
            cout<<endl<<endl<<"           "<<flag<<" USER FOUND:   DISPLAYING THE DETAILS  "<<endl;
            cout << "============================================================="<<endl<<endl;
            cout<<"Name: "<<find(line,3)<<" "<<find(line,4)<<endl;
            cout<<"Age: "<<find(line,6)<<endl;
            cout<<"Gender: "<<find(line,7)<<endl;
            cout<<"Blood Group: "<<find(line,8)<<endl;
            cout<<"City: "<<find(line,5)<<endl;
            cout<<"Email-id: "<<find(line,1)<<endl;
            cout<<"Contact Number: "<<find(line,9)<<endl;
            cout<<"No of doses: "<<find(line,10)<<endl; 

            // To check if the booking has been made
            if(find(line,11) ==  "1")
            {
                cout<<endl<<"Booking Status: Booked"<<endl<<endl;
                cout<<"Vaccine Name: "<<find(line,12)<<endl;
                cout<<"Slot: "<<find(line,13)<<endl;
                cout<<"Date: "<<find(line,14)<<endl;
                cout<<"Center Name: "<<find(line,15)<<endl;
            }
            // If booking has not been made
            else
            {
                cout<<endl<<"Booking Status: Not Booked"<<endl;
            }
            cout << "-------------------------------------------------------------" << endl << endl;
        }
    }
    // If the first name and last name does not match
    if(flag == 0)
    {
        cout << "" << endl;
        cout << "              NO USER EXISTS WITH THE GIVEN NAME             " << endl;
        cout << "                GOING BACK TO ADMIN MENU .....               "<<endl << endl;
    }
    // If the first name and thee last name matches
    else
    {
        cout << "           DETAILS OF THE USER HAS BEEN DISPLAYED            "<<endl<<endl;
        cout << "                GOING BACK TO ADMIN MENU .....               "<<endl<<endl;
    }
    check.close(); // Closing the file
}

// Function to search by the gender
void admin::search(string gender)
{
    int flag = 0;
    string line;
    // Iv the gender entered by admin is male female or other
    if(gender== "male" || gender == "female"|| gender == "other")
    {
        ifstream check;
        check.open("userdetails.csv"); // Opening the file
        
        cout << endl << "                 DISPLAYING ALL "<<gender<<" USERS   " << endl;
        cout << "============================================================="<<endl;

        while(getline(check,line))
        {
            // If the gender entered is same the one to find
            if(find(line,7) == gender)
            {
                flag++;
                cout<<"           "<<flag<<" USER FOUND:   DISPLAYING THE DETAILS "<<endl << endl;
                cout<<"Name: "<<find(line,3)<<" "<<find(line,4)<<endl;
                cout<<"Age: "<<find(line,6)<<endl;
                cout<<"Gender: "<<find(line,7)<<endl;
                cout<<"Blood Group: "<<find(line,8)<<endl;
                cout<<"City: "<<find(line,5)<<endl;
                cout<<"Email-id: "<<find(line,1)<<endl;
                cout<<"Contact Number: "<<find(line,9)<<endl;
                cout<<"No of doses: "<<find(line,10)<<endl; 
                
                // If booking has been made, displaying the booking details
                if(find(line,11) ==  "1")
                {
                    cout<<endl<<"Booking Status: Booked"<<endl<<endl;
                    cout<<"Vaccine Name: "<<find(line,12)<<endl;
                    cout<<"Slot: "<<find(line,13)<<endl;
                    cout<<"Date: "<<find(line,14)<<endl;
                    cout<<"Center Name: "<<find(line,15)<<endl;
                }
                // No booking has been made
                else
                {
                    cout<<endl<<"Booking Status: Not Booked"<<endl;
                }
                cout << "-------------------------------------------------------------" << endl;
            }
        }
        check.close(); // File closed
        if(flag == 0)
        {
            cout << "             NO USER EXISTS WITH THE GIVEN GENDER            "<<endl<<endl;
            cout << "                GOING BACK TO ADMIN MENU .....               "<<endl;
        }
        else
        {
            cout <<endl<< "       DETAILS OF ALL "<<gender<<" USERS HAVE BEEN DISPLAYED   "<<endl<<endl;
            cout << "                 GOING BACK TO ADMIN MENU .....              "<<endl<<endl;;
        }
    }
    else
    {
        cout << endl << "         PLEASE ENTER A GENDER FROM THE GIVEN OPTIONS        " << endl;
        cout << "-------------------------------------------------------------" << endl << endl;
        string gender;
        cout << "Enter Gender from the Following Options (male/female/other)" << endl;
        cout << "Gender: ";
        cin>>gender; // Again asking the user for the gender
        search(gender);
    }       
}

// Function to search the details by the city
void admin::search()
{
    int flag = 0;
    string city,line;
    cout<<"Choose your city from the following options\n(Delhi / Mumbai / Bangalore / Chennai / Kolkata) "<<endl<<endl;
    cout << "City: ";
    cin>>city;
    // If the city is from the above 5
    if(city== "Delhi" || city== "Mumbai"|| city== "Bangalore" || city== "Chennai" || city== "Kolkata")
    {
        ifstream check;
        check.open("userdetails.csv"); // File opened

        cout << endl << "             DISPLAYING ALL USERS IN "<<city<<endl;
        cout << "============================================================="<<endl<<endl;

        while(getline(check,line))
        {
            // If the city entered by the admin is the same city to be searched
            if(find(line,5) == city)
            {
                flag++;
                cout<<"           "<<flag<<" USER FOUND:   DISPLAYING THE DETAILS  "<<endl << endl;
                cout<<"Name: "<<find(line,3)<<" "<<find(line,4)<<endl;
                cout<<"Age: "<<find(line,6)<<endl;
                cout<<"Gender: "<<find(line,7)<<endl;
                cout<<"Blood Group: "<<find(line,8)<<endl;
                cout<<"City: "<<find(line,5)<<endl;
                cout<<"Email-id: "<<find(line,1)<<endl;
                cout<<"Contact Number: "<<find(line,9)<<endl;
                cout<<"No of doses: "<<find(line,10)<<endl; 

                // If booking has been made
                if(find(line,11) ==  "1")
                {
                    cout<<endl<<"Booking Status: Booked"<<endl<<endl;
                    cout<<"Vaccine Name: "<<find(line,12)<<endl;
                    cout<<"Slot: "<<find(line,13)<<endl;
                    cout<<"Date: "<<find(line,14)<<endl;
                    cout<<"Center Name: "<<find(line,15)<<endl;
                }
                // If no booking has been made
                else
                {
                    cout<<endl<<"Booking Status: Not Booked"<<endl;
                }
                cout << "-------------------------------------------------------------" << endl << endl;
            }
        }
        check.close(); // File closed
        if(flag == 0) // If no users are found
        {
            cout << "              NO USER EXISTS IN THE GIVEN CITY               " << endl;
            cout << "               GOING BACK TO ADMIN MENU .....                " << endl;
        }
        else // Users are found
        {
            cout << " DETAILS OF ALL THE USERS IN "<<city<<" HAVE BEEN DISPLAYED  "<<endl<<endl;
            cout << "               GOING BACK TO ADMIN MENU .....                "<<endl<<endl;
        }
    }
    else // Wrong city is entered by the admin
    {
        cout << endl << "          PLEASE ENTER A CITY FROM THE GIVEN OPTIONS         " << endl;
        cout << "-------------------------------------------------------------" << endl << endl;
        search(); // Again calling the search function
    }       
}

// Function to search for users based on the booking status
void admin::search(int booking_status)
{
    string line;
    // If the booking status is booked
    if(booking_status == 1)
    {
        int flag = 0;
        ifstream check;
        check.open("userdetails.csv"); // File opened

        cout << endl << "       DISPLAYING ALL USERS WITH BOOKING STATUS: BOOKED      " << endl;
        cout << "============================================================="<<endl<<endl;
        getline(check,line); // Fetching data from the file
        while(getline(check,line))
        {
            if(find(line,11) == "1")
            {
                flag++;
                cout<<"           "<<flag<<" USER FOUND: * DISPLAYING THE DETAILS *"<<endl << endl;
                cout<<"Name: "<<find(line,3)<<" "<<find(line,4)<<endl;
                cout<<"Age: "<<find(line,6)<<endl;
                cout<<"Gender: "<<find(line,7)<<endl;
                cout<<"Blood Group: "<<find(line,8)<<endl;
                cout<<"City: "<<find(line,5)<<endl;
                cout<<"Email-id: "<<find(line,1)<<endl;
                cout<<"Contact Number: "<<find(line,9)<<endl;
                cout<<"No of doses: "<<find(line,10)<<endl; 
                cout<<endl<<"Booking Status: Booked"<<endl<<endl;
                cout<<"Vaccine Name: "<<find(line,12)<<endl;
                cout<<"Slot: "<<find(line,13)<<endl;
                cout<<"Date: "<<find(line,14)<<endl;
                cout<<"Center Name: "<<find(line,15)<<endl;

                cout << "-------------------------------------------------------------" << endl << endl;
            }
        }
        check.close(); // File closed
        // If there are no details to display
        if(flag == 0)
        {
            cout << "            NO USER HAS BOOKED AN APPOINTMENT YET            " << endl << endl;
            cout << "                GOING BACK TO ADMIN MENU .....               " << endl << endl;
        }
        // If the details are displayed
        else
        {
            cout << "DETAILS OF ALL THE USERS WITH APPOINTMENTS HAVE BEEN DISPLAYED" <<endl<<endl;
            cout << "                GOING BACK TO ADMIN MENU .....                "<<endl<<endl;
        }
    }
    // If the booking status is not booked
    if(booking_status == 0)
    {
        int flag = 0;
        ifstream check;
        check.open("userdetails.csv"); // File opened

        cout << endl << "     DISPLAYING ALL USERS WITH BOOKING STATUS: NOT BOOKED    " << endl;
        cout << "============================================================="<<endl<<endl;

        while(getline(check,line)) // Fetching data from the file
        {
            if(find(line,11) == "0")
            {
                flag++;
                cout<<endl<<"           "<<flag<<" USER FOUND: * DISPLAYING THE DETAILS *"<<endl << endl;
                cout<<"Name: "<<find(line,3)<<" "<<find(line,4)<<endl;
                cout<<"Age: "<<find(line,6)<<endl;
                cout<<"Gender: "<<find(line,7)<<endl;
                cout<<"Blood Group: "<<find(line,8)<<endl;
                cout<<"City: "<<find(line,5)<<endl;
                cout<<"Email-id: "<<find(line,1)<<endl;
                cout<<"Contact Number: "<<find(line,9)<<endl;
                cout<<"No of doses: "<<find(line,10)<<endl; 
                cout<<endl<<"Booking Status: Not Booked"<<endl<<endl;
                
                cout << "-------------------------------------------------------------" << endl<<endl;
            }
        }
        check.close(); // File closed
        // If there are no details to display
        if(flag == 0)
        {
            cout << "            ALL USERS HAVE BOOKED AN APPOINTMENT             "<<endl<<endl;
            cout << "                 GOING BACK TO ADMIN MENU .....              "<<endl;
        }
        // If the details are displayed
        else
        {
            cout << "DETAILS OF ALL THE USERS WITH NO APPOINTMENTS HAVE BEEN DISPLAYED" <<endl<<endl;
            cout << "                  GOING BACK TO ADMIN MENU .....                 "<<endl<<endl;
        }
       
    }       
}

// Function to delete the user details by their name
void admin::delete_by_name()
{
    cout << "" << endl;
    int flag = 0;
    string fname,lname,line;
    cout<< "Enter First Name: ";
    cin>>fname;
    cout<< "Enter Last Name: ";
    cin>>lname;

    ifstream details;
    details.open("userdetails.csv"); // File opened
    
    while(getline(details,line))
    {
        if(find(line,3) == fname && find(line,4) == lname)
        {
            flag = 1;
            cout<<"User Found !!!"<<endl;
        }
    }
    details.close(); // File closed
    if(flag == 1)
    {
        ifstream details;
        details.open("userdetails.csv");
        ofstream temp;
        temp.open("temp.csv");
        while(getline(details, line))
        {
            if (find(line,3) != fname && find(line,4) != lname)
            {
                temp<<line<<endl;
            }
        }
        temp.close(); // Temp file closed
        details.close(); // Main file closed
        remove("userdetails.csv"); // Main file deleted
        rename("temp.csv","userdetails.csv"); // Temp file renamed as the main file
        cout << "" << endl;
        cout << "                       ACCOUNT DELETED                       "<<endl; 
        cout << "                GOING BACK TO ADMIN MENU .....               "<<endl<<endl;   
    }
    else
    {
        cout << "-------------------------------------------------------------" << endl << endl;
        cout << "             NO USER EXISTS WITH THE GIVEN NAME              "<<endl;
        cout << "                 ACCOUNT CANNOT BE DELETED                   "<<endl << endl;
        cout << "               GOING BACK TO ADMIN MENU .....                "<<endl<<endl;
    }
}

// Choice Function
void input_choice() 
{
    //user_details user_obj; // Temporary object created for the class
    int int_choice=0;
    while(int_choice!=4)
    {
        int int_choice;
        string choice;
        cout << "=============== VACCINATION MANAGEMENT SYSTEM ===============" << endl;
        cout << "" << endl;
        cout << "                ---------- Welcome ----------                " << endl;
        cout << "" << endl;
        cout << "" << endl;
        cout << "Please choose from the following options: -\n1. LOGIN\n2. SIGN UP\n3. ADMIN LOGIN\n4. EXIT\n" << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        for(int i=0;i<choice.length();i++)
        {
            if(!isdigit(choice[i]))
            {
                cout<<""<<endl;
                cout << "                 PLEASE ENTER A VALID CHOICE                 " << endl;
                cout<<"\n"<<endl;
                input_choice();
                return;
            }
        }
        int_choice=stoi(choice);

        switch(int_choice)  // Switch case
        {
        case 1: 
            cout << "" << endl;
            book_obj.user_login(); // Login function call
            book_obj.display();
            book_obj.login_choice();
            break;
        case 2: 
            cout << "" << endl;
            book_obj.signup(); // Signup function call
            break;
        case 3: 
            cout << "" << endl;
            admin_login();
            break;
        case 4:
            cout << "" << endl;
            cout << "============================================================="<<endl<<endl;
            cout<<  "                     SUCCESSFULLY EXITED                     "<<endl<<endl;
            cout << "============================================================="<<endl<<endl;
            std::exit(0); // Exiting the program
        default:
            cout << "" << endl;
            cout << "                 PLEASE ENTER A VALID CHOICE                 " << endl;
            cout << "\n\n";
            input_choice(); // Recursively calling the function till the user enters the correct choice
            return;
        }
    }
}

// Main Function
int main() 
{
    cout << "\n\n" <<  endl;
    input_choice(); // Asking for user choice
    return(0);
}