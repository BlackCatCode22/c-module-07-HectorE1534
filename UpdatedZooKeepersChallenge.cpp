#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>    
#include <ctime>      
#include <sstream>
#include <chrono>
#include <iomanip>

// Function to trim whitespace from start and end of string
std::string trim(const std::string& str) 
{
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}
// Created own date handling because for some reason the other codes were not working
class Date 
{
private:
    int year;
    int month;
    int day;

public:
    Date(int y, int m, int d) : year(y), month(m), day(d) {}
    
    // Constructor sets to current date
    Date() 
    {
        time_t t = time(nullptr);
        struct tm* now = localtime(&t);
        year = now->tm_year + 1900;
        month = now->tm_mon + 1;
        day = now->tm_mday;
    }
    
    // Getters
    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
    
    // Format date as string
    std::string toString() const 
    {
        std::ostringstream oss;
        oss << year << '-' 
            << std::setw(2) << std::setfill('0') << month << '-'
            << std::setw(2) << std::setfill('0') << day;
        return oss.str();
    }
};

// Function to get current date in ISO format
std::string getCurrentDateISO() 
{
    Date today;
    return today.toString();
}

// Function to calculate birthday based on age and season
Date calcAnimalBirthday(int age, const std::string& birthSeason) 
{
    // Get current date
    time_t t = time(nullptr);
    struct tm* now = localtime(&t);
    int currentYear = now->tm_year + 1900;
    
    // Calculate birth year based on age
    int birthYear = currentYear - age;
    
    // Determine birth month and day based on season
    int birthMonth = 1;

    // Default to middle of month
    int birthDay = 15; 
    
    if (birthSeason == "spring") 
    {
        birthMonth = 4; // April
    }
     else if (birthSeason == "summer") 
    {
        birthMonth = 7; // July
    }
     else if (birthSeason == "fall") 
    {
        birthMonth = 10; // October
    }
     else if (birthSeason == "winter") 
    {
        birthMonth = 1; // January
    }
    
    // Create and return the date
    return Date(birthYear, birthMonth, birthDay);
}

//Making Base Animal class, encapsulation.
class Animal 
{
protected:
    std::string name;
    std::string id;
    int age;
    std::string sex;
    std::string species;
    std::string color;
    int weight;
    Date birthDate; 
    std::string birthSeason; 
    std::string location;
    
public:
    // Constructor
    Animal(const std::string& n, const std::string& i, int a, const std::string& s, const std::string& p, 
           const std::string& c, int w, const std::string& bs, const std::string& l = "unknown")
     : name(n), id(i), age(a), sex(s), species(p), color(c), weight(w), birthSeason(bs), location(l) {

        // Calculate birthdate based on age and birth season
        birthDate = calcAnimalBirthday(age, birthSeason);
    }

    // Virtual destructor for proper cleanup
    virtual ~Animal() {}
    
    // Getters
    std::string getName() const { return name; }
    std::string getId() const { return id; }
    int getAge() const { return age; }
    std::string getSex() const { return sex; }
    std::string getSpecies() const { return species; }
    std::string getColor() const { return color; }
    int getWeight() const { return weight; }
    Date getBirthDate() const { return birthDate; }
    std::string getBirthDateString() const { return birthDate.toString(); }
    std::string getBirthSeason() const { return birthSeason; }
    std::string getLocation() const { return location; }

     // Setters
     void setName(const std::string& n) { name = n; }
     void setId(const std::string& i) { id = i; }
     void setAge(int a) 
     { 
         age = a; 
         // Update birthdate when age changes
         birthDate = calcAnimalBirthday(age, birthSeason);
     }
     void setSex(const std::string& s) { sex = s; }
     void setSpecies(const std::string& p) { species = p; }
     void setColor(const std::string& c) { color = c; }
     void setWeight(int w) { weight = w; }
     void setBirthSeason(const std::string& bs) 
     { 
         birthSeason = bs; 
         // Update birthdate when season changes
         birthDate = calcAnimalBirthday(age, birthSeason);
     }
     void setLocation(const std::string& l) { location = l; };
     

    // Virtual method for polymorphism
     virtual void makeSound() const 
     {
        std::cout << name << " makes a sound" << std::endl; 
     }
     
     // Method to display animal info including birthday
     void displayInfo() const 
     {
         std::cout << "Name: " << name << "\n"
                   << "ID: " << id << "\n"
                   << "Species: " << species << "\n"
                   << "Age: " << age << " years\n"
                   << "Sex: " << sex << "\n"
                   << "Color: " << color << "\n"
                   << "Weight: " << weight << " pounds\n"
                   << "Estimated Birth Date: " << getBirthDateString() << "\n";
                   std::cout << "Location: " << location << "\n";
     }
};

// Hyena subclass, Inheritance
class Hyena : public Animal 
{
public:
    Hyena(const std::string& name, const std::string& id, int age, const std::string& sex, const std::string& color, 
          int weight, const std::string& birthSeason, const std::string& location = "unknown") 
    : Animal(name, id, age, sex, "Hyena", color, weight, birthSeason, location) {}

    // Override makeSound for polymorphism
    void makeSound() const override 
    { 
        std::cout << getName() << " laughs hysterically" << std::endl; 
    }
};

// Lion subclass
class Lion : public Animal 
{
public:
    Lion(const std::string& name, const std::string& id, int age, const std::string& sex, const std::string& color, 
         int weight, const std::string& birthSeason, const std::string& location = "unknown") 
    : Animal(name, id, age, sex, "Lion", color, weight, birthSeason, location) {}

    void makeSound() const override 
    { 
        std::cout << getName() << " roars majestically" << std::endl; 
    }
};

// Tiger subclass
class Tiger : public Animal 
{
public:
    Tiger(const std::string& name, const std::string& id, int age, const std::string& sex, const std::string& color, 
          int weight, const std::string& birthSeason, const std::string& location = "unknown") 
    : Animal(name, id, age, sex, "Tiger", color, weight, birthSeason, location) {}

    void makeSound() const override 
    { 
        std::cout << getName() << " growls fiercely" << std::endl; 
    }
};

// Bear subclass
class Bear : public Animal 
{
public:
    Bear(const std::string& name, const std::string& id, int age, const std::string& sex, const std::string& color, 
         int weight, const std::string& birthSeason, const std::string& location = "unknown")
     : Animal(name, id, age, sex, "Bear", color, weight, birthSeason, location) {}

    void makeSound() const override 
    { 
        std::cout << getName() << " grunts loudly" << std::endl; 
    }
};

// Function to parse animal names
std::map<std::string, std::vector<std::string> > parseAnimalNames(const std::string& filename) 
{
    std::map<std::string, std::vector<std::string> > nameMap;
    std::ifstream nameFile(filename.c_str());
    
    if (!nameFile) 
    {
        std::cerr << "Error opening name file: " << filename << std::endl;
        return nameMap;
    }
    
    std::string line;
    std::string currentSpecies = "";
    
    while (getline(nameFile, line)) 
    {
        // Check if this is a category line (ends with "Names:")
        if (line.find(":") != std::string::npos) 
        {
            // Extract species name (remove "Names:")
            currentSpecies = line.substr(0, line.find(" "));
            continue;
        }
        
        // Parse individual names (they're comma-separated)
        size_t pos = 0;
        while (pos < line.length()) 
        {
            // Trim leading spaces
            size_t startPos = line.find_first_not_of(" \t", pos);
            if (startPos != std::string::npos)
                pos = startPos;

            // Reached end of line
            if (pos >= line.length()) break;

            // Find comma or end of string
            size_t endPos = line.find(",", pos);
            if (endPos == std::string::npos) 
            {
                // End of line, so trim whitespace
                endPos = line.find_last_not_of(" \t\n");
                if (endPos == std::string::npos) break;
                endPos++;
            }
            
            // Extract name
            std::string name = trim(line.substr(pos, endPos - pos));
                
            // Add name to appropriate list if it's not empty or just whitespace, this is also to prevent empty names
            if (!name.empty() && !currentSpecies.empty())
            nameMap[currentSpecies].push_back(name);
            
            // Move to next name
            pos = endPos + 1;
        }
    }
    
    nameFile.close();
    return nameMap;
}

// Function to get a random name and remove it from the available names
std::string getRandomName(std::vector<std::string>& names) 
{
    if (names.empty()) return "Unnamed";
    
    // Create a new vector with only non-empty names
    std::vector<std::string> validNames;
    for (const auto& name : names) 
    {
        if (!name.empty() && name != " ") 
        {
            validNames.push_back(name);
        }
    }
    
    // If no valid names were found, return default
    if (validNames.empty()) return "Unnamed";
    
    // Select random name from valid options
    int index = rand() % validNames.size();
    std::string selectedName = validNames[index];
    
    // Remove the selected name from the original vector
    for (auto it = names.begin(); it != names.end(); ++it) 
    {
        if (*it == selectedName) 
        {
            names.erase(it);
            break;
        }
    }
    
    return selectedName;
}

// Function to extract birth season from text
std::string parseBirthSeason(const std::string& line) 
{
    if (line.find("born in spring") != std::string::npos) 
    {
        return "spring";
    }
     else if (line.find("born in summer") != std::string::npos) 
    {
        return "summer";
    }
     else if (line.find("born in fall") != std::string::npos) 
    {
        return "fall";
    }
     else if (line.find("born in winter") != std::string::npos) 
    {
        return "winter";
    }
    return "unknown";
}

int main() 
{
    srand(static_cast<unsigned int>(time(NULL)));
    std::vector<Animal*> animals;
    std::map<std::string, int> speciesCount;
    
    std::cout << "Today's date: " << getCurrentDateISO() << std::endl;
    
    // Parse animal names first
    std::map<std::string, std::vector<std::string> > namesBySpecies = parseAnimalNames("animalNames.txt");
    
    // Create a copy of namesBySpecies that we'll modify as we use names
    std::map<std::string, std::vector<std::string> > availableNames = namesBySpecies;
    
    // Read from input file
    std::ifstream inFile("arrivingAnimals.txt");
    if (!inFile) 
    {
        std::cerr << "Error opening input file" << std::endl;
        return 1;
    }
    
    std::string line;
    while (getline(inFile, line)) 
    {
        std::string id = "";
        int age = 0;
        std::string sex = "", species = "", color = "";
        int weight = 0;
        std::string location = "";

        // Parse Age
        if (isdigit(line[0])) 
        {
            age = atoi(line.c_str());
        }

        // Parse sex
        if (line.find("female") != std::string::npos) 
        {
            sex = "Female";
        }
         else if (line.find("male") != std::string::npos) 
        {
            sex = "Male";
        }

        // Parse weight using pounds as keyword
        size_t weightPos = line.find("pounds");
        if (weightPos != std::string::npos) 
        {
            // Go backwards from "pounds" to find the start of the number
            size_t end = weightPos - 1;

            // Skip any spaces
            while (end > 0 && isspace(line[end])) end--;

            // Find the start of the number
            size_t start = end;
            while (start > 0 && isdigit(line[start-1])) start--;

            // Extract and convert to int
            if (end >= start) 
            {
                std::string weightStr = line.substr(start, end - start + 1);
                weight = atoi(weightStr.c_str());
            }
        }

        // Parse species
        if (line.find("hyena") != std::string::npos) 
        {
            species = "Hyena";
        }
         else if (line.find("lion") != std::string::npos) 
        {
            species = "Lion";
        }
         else if (line.find("tiger") != std::string::npos) 
        {
            species = "Tiger";
        }
         else if (line.find("bear") != std::string::npos) 
        {
            species = "Bear";
        }

        // Parse birth season
        std::string birthSeason = parseBirthSeason(line);

        // Use comma-based parsing for color, weight, and location
        std::vector<std::string> segments;
        std::istringstream ss(line);
        std::string segment;
        
        while (std::getline(ss, segment, ',')) 
        {
            segments.push_back(trim(segment));
        }
        
        if (segments.size() >= 6) 
        {
            // Third segment: Color (e.g., "tan color")
            std::istringstream colorInfo(segments[2]);
            std::string colorStr, colorWord;
            
            while (colorInfo >> colorWord && colorWord != "color") 
            {
                if (!colorStr.empty()) colorStr += " ";
                colorStr += colorWord;
            }
            
            color = colorStr;

            // Capitalize first letter of color
            if (!color.empty()) 
            {
                color[0] = std::toupper(color[0]);
            }
            
            // Fourth segment: Weight (e.g., "70 pounds")
            std::istringstream weightInfo(segments[3]);
            std::string weightStr, poundStr;
            
            if (weightInfo >> weightStr >> poundStr) 
            {
                weight = std::stoi(weightStr);
            }
            
            // Fifth segment: Location (e.g., "from Friguia Park, Tunisia")
            if (segments[4].find("from ") != std::string::npos) 
            {
                location = segments[4].substr(5); // Skip "from "
                
                // Check if there's a country part in segment 5
                if (segments.size() > 5) 
                {
                    location += ", " + segments[5];
                }
            } 
            else 
            {
                location = segments[4];
                // Check if there's a country part in segment 5
                if (segments.size() > 5) 
                {
                    location += ", " + segments[5];
                }
            }
        }

        if (!species.empty()) 
        {
            speciesCount[species]++;

            // Generate ID
            std::string id = species + "_" + std::to_string(speciesCount[species]);            
            
            // Get random name for this species
            std::string animalName;
            if (availableNames.find(species) != availableNames.end() && !availableNames[species].empty()) 
            {
                animalName = getRandomName(availableNames[species]);
            }
            else 
            {
                // Use default naming if no names available
                char buffer[50];
                sprintf(buffer, "%s%d", species.c_str(), speciesCount[species]);
                animalName = buffer;
            }
            
            if (species == "Hyena") animals.push_back(new Hyena(animalName, id, age, sex, color, weight, birthSeason, location));
            else if (species == "Lion") animals.push_back(new Lion(animalName, id, age, sex, color, weight, birthSeason, location));
            else if (species == "Tiger") animals.push_back(new Tiger(animalName, id, age, sex, color, weight, birthSeason, location));
            else if (species == "Bear") animals.push_back(new Bear(animalName, id, age, sex, color, weight, birthSeason, location));
            else std::cerr << "Unknown species: " << species << std::endl;
        }
    }

    inFile.close();
    
    std::ofstream outFile("zooPopulation.txt");
    if (!outFile) 
    {
        std::cerr << "Error opening output file" << std::endl;
        return 1;
    }
    
    for (std::map<std::string, int>::iterator it = speciesCount.begin(); it != speciesCount.end(); ++it) 
    {
        outFile << it->first << "s:" << std::endl;
        for (size_t i = 0; i < animals.size(); i++) 
        {
            if (animals[i]->getSpecies() == it->first) 
            {
                outFile << " -" << animals[i]->getName() << "\n"
                       << "     ID: " << animals[i]->getId() << "\n"
                       << "     Color: " << animals[i]->getColor() << "\n"
                       << "     Sex: " << animals[i]->getSex() << "\n"
                       << "     Age: " << animals[i]->getAge() << "\n"
                       << "     Weight: " << animals[i]->getWeight() << "\n"
                       << "     Estimated Birth Date: " << animals[i]->getBirthDateString() << "\n"
                       << "     Location: " << animals[i]->getLocation()<< "\n"
                       << "\n";
            }
        }
        outFile << "Total " << it->first << "s: " << it->second << "\n\n";
    }
    
    outFile.close();
    std::cout << "Animal report generated successfully!\n";
    
    std::cout << "\nAnimal Information:" << std::endl;
    for (size_t i = 0; i < animals.size() && i < 16; i++) 
    {
        std::cout << "\n------------ Animal #" << (i+1) << " ------------\n";
        animals[i]->displayInfo();
    }
    
    std::cout << "\n... All Animals Shown!" << std::endl;
    
    // Clean up
    for (size_t i = 0; i < animals.size(); i++) delete animals[i];
    return 0;
}