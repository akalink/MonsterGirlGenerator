#include <iostream>
#include <string>
//#include <ctime>
using namespace std;

struct bustSize {
    int num = 0;
    string discription;
};
struct buttSize {
    int num = 0;
    string discription;
};
struct hairType{
    string length;
    string style;
    string color;
};
struct furType{
    bool hasFur = false;
    string type;
    string color;
    bool isOni = false;
};
struct faceType{
    string faceShape;
    string faceMood;
    string eyes;
};
//structure to hold all character data
struct monsterGirlStats {
    string name;
    string species;
    furType FSF;
    int height = 0;
    bustSize bust;
    hairType hair;
    string skin;
    faceType face;
    buttSize butt;
    string personality;
    string snack;
    string sex;
    string gender;
    bool isBoy = false;
    string occ;
    string hob;
};
// convert string data to a useable format
int getRandfromString(string name){
    int seed = 0;
    for (int i = 0; i < name.length(); i ++) {
        seed += 1;
        if (isalpha(name.at(i))) {
            seed += 2;
            if (isupper(name.at(i))) {
                seed += 2;
            } else {
                seed += 1;
            }
        }
        seed += name.at(i);
    }
return seed;
}
int selectSpecies();
string getSpecies(int& height, bool& FSF, int& bust, string& skin,bool& isO);
int getMeasurement(int specHeight, int range);
string getBustSize(int value);
string getHair(string& color,string& style, bool FSF, string&FSFColor, bool boy);
string getBody(string& fshape, string&fmood, string& eyeColor, bool isO);
int getButt(int bust);
void getPersonality(string& per, int& height, int& bust, int& butt);
string getTaste(int& bust);
string getSexuality(bool boy);
string getGender(int& bust, int& butt, bool boy);
string getHobbie();
string getJob();
bool getBoy();
string getShredded(int bust, string descript);
int main() {
    monsterGirlStats userMon;
    bool loopGenerator = true;
    cout << "----------------------" << endl;
    cout << "Monster Girl Generator" << endl;
    cout << "----------------------" << endl;

    char checkInput;

    while(loopGenerator) {
        while (true) {
            cout << "Create Monster Girl of Boy (G/B): ";
            cin >> checkInput;
            if ((checkInput == 'G') || (checkInput == 'g')) {
                userMon.isBoy = false;
                break;
            } else if ((checkInput == 'B') || (checkInput == 'b')) {
                userMon.isBoy = true;
                userMon.height += 3;
                break;
            }
            cout << "Invalid Input" << endl;
        }
        cin.ignore();
        cout << "Input a name to create your monster ";
        if(userMon.isBoy){
            cout << "boy: ";
        } else {
            cout << "girl: ";
        }
        getline(cin, userMon.name);
        cout << "Use name to generate? (y/n)" << endl;
        cin >> checkInput;
        if ((checkInput == 'y') || (checkInput == 'Y')) {
            srand(getRandfromString(userMon.name));
        } else {
            srand(time(NULL));
        }
        //sets characters species as well as set modifiers and set checks for non human part checks
        userMon.species = getSpecies(userMon.height, userMon.FSF.hasFur, userMon.bust.num,
                                     userMon.FSF.type, userMon.FSF.isOni);
        //in inches, 1 foot range, 5 foot base
        userMon.height = getMeasurement(userMon.height, 12) + 60;
        //generates a number 0-99 to determine bust size. Added to species bust modifier
        userMon.bust.num = getMeasurement(userMon.bust.num, 100);
        //userMon.isBoy = getBoy(); old function to randomly generate as boy
        userMon.skin = getBody(userMon.face.faceShape, userMon.face.faceMood, userMon.face.eyes, userMon.FSF.isOni);
        userMon.hair.length = getHair(userMon.hair.color, userMon.hair.style, userMon.FSF.hasFur, userMon.FSF.color,
                                      userMon.isBoy);
        //uses bust size to determine butt size. Made because more often "top heavy" than "curvy" was generated
        userMon.butt.num = getButt(userMon.bust.num);
        userMon.butt.num = getMeasurement(abs(userMon.butt.num), abs(100 - userMon.butt.num));
        //generates personality, personality also affects other integer stats.
        getPersonality(userMon.personality, userMon.height, userMon.bust.num, userMon.butt.num);
        //snacks influence bust size
        userMon.snack = getTaste(userMon.bust.num);
        //chance to create trans and non-binary monster
        userMon.gender = getGender(userMon.bust.num, userMon.butt.num, userMon.isBoy);
        //chance to be gay, bi, etc
        userMon.sex = getSexuality(userMon.isBoy);
        //check species and isBoy to create scrawny or skinny boy using bust number.
        if (userMon.isBoy) {
            userMon.bust.discription = getShredded(userMon.bust.num, userMon.species);
        } else {
            userMon.bust.discription = getBustSize(userMon.bust.num);
            userMon.butt.discription = getBustSize(userMon.butt.num);
        }
        //assigns hobbie and job randomly
        userMon.hob = getHobbie();
        userMon.occ = getJob();

        //// outputs results

        cout << endl << "----------------------" << endl;
        cout << "Name: " << userMon.name << endl;
        cout << "Species: " << userMon.species << endl;
        cout << "Personality: " << userMon.personality << endl;
        cout << "Favorite Snacks: " << userMon.snack << endl;
        cout << "Favorite Hobby: " << userMon.hob << endl;
        cout << "Occupation: " << userMon.occ << endl;
        cout << "Height: " << (userMon.height / 12) << " Feet " << (userMon.height % 12) << " Inches" << endl;
        cout << "Gender: " << userMon.gender << endl;
        cout << "Sexuality: " << userMon.sex << endl;
        if (userMon.isBoy) {
            cout << "Body: " << userMon.bust.discription << endl;
        } else {
            cout << "Bust Size: " << userMon.bust.discription << endl;
            cout << "Butt Size: " << userMon.butt.discription << endl;
        }
//        cout << userMon.bust.num << endl;

//        cout << userMon.butt.num << endl;
        cout << "Skin Color: " << userMon.skin << endl;
        cout << "Face: " << userMon.face.faceShape << " " << userMon.face.faceMood << " face" << endl;
        cout << "Eyes: " << userMon.face.eyes << endl;
        cout << "Hair : " << userMon.hair.length << " " << userMon.hair.style << " " << userMon.hair.color << " hair"
             << endl;
        if (userMon.FSF.hasFur) {
            cout << userMon.FSF.type << " Color: " << userMon.FSF.color << endl;
        }
        userMon.height = 0;
        userMon.bust.num = 0;
        userMon.butt.num = 0;
        userMon.FSF.isOni = false;
        cout << endl << "Generate another character? (y/n): " << endl;
        loopGenerator = false;
        cin >> checkInput;
        if((checkInput == 'Y') || (checkInput == 'y')){
            loopGenerator = true;
        }
    }

    return 0;
}
int selectSpecies(){
    int g = rand() % 16;
    int userinput;
    cout << "Use Generator or select species (input number);" << endl;
    cout << "0. Random" << endl << "1. Select Species ";
    cin >> userinput;
    if(userinput == 0) {
        return g;
    }
    while(true)
    {
        cout << "Select species (input number):" << endl;
        cout << " 0: Arachne  " << " 1. Centaur  " << " 2. Elf      " << " 3. Demon" << endl;
        cout << " 4. Dragon   " << " 5. Harpy    " << " 6. Kitsune  " << " 7. Lamia" <<  endl;
        cout << " 8. Mermaid  " << " 9. Minotaur " << "10. Moth     " << "11. Oni" << endl;
        cout << "12. Satyr    " << "13. Sphinx   " << "14. Vampire  " << "15. Werewolf" << endl;
        cin >> userinput;
        if (abs(userinput) > 15){
            cout << "Not valid range" << endl;
        } else{
            return userinput;
        }
    }

}
string getSpecies(int& height, bool& FSF, int& bust, string& skin, bool& isO){
    int g = selectSpecies();
    switch (g){
        case 0: FSF = true; height -= 5, height -= 2; bust -=10; skin = "Fur"; return "Arachne";
        case 1: FSF = true; height += 8; bust += 25; skin = "Fur"; return "Centaur";
        case 2: FSF = false; height += 2; bust -= 3; return "Elf";
        case 3: FSF = false; bust += 10; return "Demon";
        case 4: FSF = true; height += 12; bust += 20; skin = "Scales"; return "Dragon";
        case 5: FSF = true; height -= 4; bust -= 30; skin = "Feathers"; return "Harpy";
        case 6: FSF = true; height -= 2; bust -= 10; skin = "Fur"; return "Kitsune";
        case 7: FSF = true; bust += 10; skin = "Scales"; return "Lamia";
        case 8: FSF = true; bust -= 5; skin = "Scales"; return "Mermaid";
        case 9: FSF = true; height += 18; bust += 40; skin = "Fur"; return "Minotaur";
        case 10: FSF = true; height -= 7; bust -= 15; skin = "Fur"; return "Moth";
        case 11: FSF = false; height += 30; bust += 15; isO = true; return "Oni";
        case 12: FSF = true; height -= 6; bust -= 10; skin = "Fur"; return "Satyr";
        case 13: FSF = true; height += 2; bust += 5; skin = "Fur"; return "Sphinx";
        case 14: FSF = false; return "Vampire";
        default: FSF = true; height += 3; bust += 5; skin = "Fur"; return "Werewolf";
    }
}
int getMeasurement(int specHeight, int range){
    int g = specHeight + (rand() % range);
//    cout << g << endl;
    return g;
}
string getBustSize(int value){
//    cout << value << endl;
    if (value < 15){
        return "Flat";
    } else if (value < 45){
        return "Small";
    } else if (value < 75){
        return "Average";
    } else if (value < 100){
        return "Large";
    } else if (value < 130){
        return "Huge";
    } else {
        return "Gigantic";
    }

}
string getHair(string& color,string& style, bool FSF, string& FSFColor, bool boy){
    int g = rand() % 9;
    if(FSF){
        switch (g){
            case 0: FSFColor = "Brown"; break;
            case 1: FSFColor = "Black"; break;
            case 2: FSFColor = "Yellow"; break;
            case 3: FSFColor = "White"; break;
            case 4: FSFColor = "Red"; break;
            case 5: FSFColor = "Blue"; break;
            case 6: FSFColor = "Green"; break;
            case 7: FSFColor = "Purple"; break;
            default: FSFColor = "Pink"; break;
        }
    }
    g = rand() % 9;
    switch (g){
        case 0: color = "brown"; break;
        case 1: color = "black"; break;
        case 2: color = "yellow"; break;
        case 3: color = "white"; break;
        case 4: color = "red"; break;
        case 5: color = "blue"; break;
        case 6: color = "green"; break;
        case 7: color = "purple"; break;
        default: color = "pink"; break;
    }
    g = rand() % 4;
    switch (g){
        case 0: style = "wavy"; break;
        case 1: style = "curly"; break;
        default: style = "straight"; break;
    }
    g = rand() % 10;
    switch (g){
        case 0:
        case 1: return "Short";
        case 2: return "Bob length";
        case 3:
        case 4: return "Medium";
        case 5:
        case 6: return "Long";
        case 7: return "Extra long";
        case 8: return "Ponytail";
        default: if(boy){return "Faux Hawk";} else{ return "To the floor";};
    }
}
string getBody(string& fshape, string&fmood, string& eyeColor, bool isO){
    int g = rand() % 4;
    switch (g) {
        case 0: fshape = "Round"; break;
        case 1: fshape = "Square"; break;
        case 2: fshape = "Triange"; break;
        default: fshape = "Oval"; break;
    }
    g = rand() % 4;
    switch (g) {
        case 0: fmood = "serious"; break;
        case 1: fmood = "cute"; break;
        case 2: fmood = "mature"; break;
        default: fmood = "baby"; break;
    }
    g = rand() % 7;
    switch (g) {
        case 0: eyeColor = "Brown"; break;
        case 1: eyeColor = "Hazel"; break;
        case 2: eyeColor = "White"; break;
        case 3: eyeColor = "Black"; break;
        case 4: eyeColor = "Blue"; break;
        case 5: eyeColor = "Yellow";
        default: eyeColor = "Glowing Green"; break;
    }
    g = rand() % 4;
    if(isO){
        switch (g % 2){
            case 0: return "Red";
            default: return "Blue";
            }
    }
    switch (g) {
        case 0: return "Black";
        case 1: return "Tanned";
        default: return "White";
    }
}
int getButt(int bust){
    if(bust < 15){
        bust = 30;
    } else if ((bust > 70) && (bust < 100)) {
        bust = 100;
    } else{
        return bust;
    }
    bust = bust / 2;

    return bust;
}
void getPersonality(string& per, int& height, int& bust, int& butt){
    switch (rand() % 2){
        case 0: per = "I"; bust *= 1.1; break;
        default: per = "E"; bust *= 0.95; break;
    }
    switch (rand() % 2){
        case 0: per += "S"; butt *= 1.2; break;
        default: per += "N"; butt *= 0.9; break;
    }
    switch (rand() % 2){
        case 0: per += "F"; bust *= 1.1; break;
        default: per += "T"; bust *= 0.9; break;
    }
    switch (rand() % 2){
        case 0: per += "J"; height += 3; break;
        default: per += "P"; height -= 2; break;
    }
}
string getTaste(int& bust){
    switch (rand() % 2){
        case 0: bust *= 1.1; return "Sweet";
        default: bust *= .95; return "Salty";
    }
}
char getinput(){
    char userInput;
    cin >> userInput;
    return userInput;
}
string getGender(int& bust, int& butt, bool boy){
    switch(rand() % 40){
        case 0: bust *= .6; butt *= .7;
            return "Trans";
        case 1: bust *= .8; butt *= .9;
            return "Non-Binary";
        default: if(boy){ return "Male";} else { return "Female";};
    }
}
string getSexuality(bool boy){
    switch(rand() % 50){
        case 0: if(boy){return "Gay";} else {return "Lesbian";};
        case 1: return "Bisexual";
        case 3: return "Pansexual";
        case 4: return "Asexual";
        default: return "Straight";
    }

}
string getHobbie(){
    switch (rand() % 23){
        case 0: return "Drawing";
        case 1: return "Building computers";
        case 2: return "Coaching";
        case 3: return "Playing in a band";
        case 4: return "Gardening";
        case 5: return "Writing";
        case 6: return "Gaming";
        case 7: return "Hiking";
        case 8: return "Fishing";
        case 9: return "Boating";
        case 10: return "Collecting comics";
        case 11: return "Playing TCG";
        case 12: return "Making youtube videos";
        case 13: return "Going to conventions";
        case 14: return "Collecting rare dolls";
        case 15: return "Looking at memes";
        case 16: return "Tabletop";
        case 17: return "Trying makeup";
        case 18: return "Modding cars";
        case 19: return "Knitting";
        case 20: return "Swimming";
        case 21: return "Watching movies";
        default: return "Cooking";
    }
}
string getJob(){
    switch(rand() % 30){
        case 0: return "Attorney";
        case 1: return "Doctor";
        case 2: return "Programmer";
        case 3: return "Nurse";
        case 4: return "Truck Driver";
        case 5: return "Teacher";
        case 6: return "Actor";
        case 7: return "Paper Pusher";
        case 8: return "A/V technician";
        case 9: return "A/C repair";
        case 10: return "Plumber";
        case 11: return "Pro Golfer";
        case 12: return "Mechanic";
        case 13: return "Game Developer";
        case 14: return "Film Composer";
        case 15: return "Student";
        case 16: return "Twitch Streamer";
        case 17: return "Politician";
        case 18: return "Sculptor";
        case 19: return "Tailor";
        case 20: return "Vet Tech";
        case 21: return "Garbage Collector";
        case 22: return "CPA";
        case 23: return "Retail Associate";
        case 24: return "Robotics Engineer";
        case 25: return "Chef";
        case 26: return "Brand representative";
        case 27: return "Graphic designer";
        case 28: return "Real Estate agent";
        default: return "Server";
    }
}
bool getBoy(){
    switch (rand() % 5){
        case 0: return true;
        default: return false;
    }
}
string getShredded(int bust, string descript){
    if((descript == "Werewolf") || (descript == "Sphinx") || (descript == "Minotaur")
        || (descript == "Oni") || (descript == "Dragon")){
        bust *= .9;
        bust += (rand() % 100);
    } else {
        bust = 0;
        bust += (rand() % 100);
    }

    if(bust < 25){
        return  "Scrawny";
    } else if (bust < 50){
        return "Slender";
    } else if (bust < 75) {
        return "Toned";
    } else if (bust < 100) {
        return "Buff";
    } else if (bust < 115) {
        return "Shredded";
    } else {
        return "Bara";
    }
//    cout << bust << endl;
}