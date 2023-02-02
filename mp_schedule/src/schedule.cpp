/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "schedule.h"
#include "utils.h"
#include <algorithm>

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename){
    // Your code here!
    V2D toReturn;
    std::string fileString = file_to_string(filename);

    std::vector<std::string> lines;
    char lineSep = '\n';
    int numLines = SplitString(fileString, lineSep, lines);
    numLines = numLines * 1;

    for(auto &s : lines) {
        std::vector<std::string> newLine;
        char elemSplit = ',';
        int numElem = SplitString(s, elemSplit, newLine);
        for(auto &e : newLine) {
            e = Trim(e);
        }
        toReturn.push_back(newLine);
    }

    return toReturn;
}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(const V2D & cv, const V2D & student){
    // YOUR CODE HERE
    V2D toReturn;

    std::unordered_map<std::string, std::vector<std::string>> studentMap;
    for(auto &v : student) {
        std::vector<std::string> stuClassList = {v.begin()+1, v.end()};
        std::pair<std::string, std::vector<std::string>> toInsert (v[0], stuClassList);
        studentMap.insert(toInsert);
    }

    for(auto &currClass : cv) {
        std::vector<std::string> finalClassList;
        finalClassList.push_back(currClass[0]);
        bool first = true;
        for(auto &checkStu : currClass) {
            if(first) {
                first = false;
                continue;
            }
            std::unordered_map<std::string, std::vector<std::string>>::const_iterator currStudent = studentMap.find(checkStu);
            if(currStudent == studentMap.end()) {
                continue;
            }
            if(std::find(currStudent->second.begin(), currStudent->second.end(), currClass[0]) != currStudent->second.end()) {
                finalClassList.push_back(checkStu);
            }
        }
        toReturn.push_back(finalClassList);
    }

    for(size_t i = 0; i < toReturn.size(); i++) {
        if(toReturn[i].size() == 1) {
            toReturn.erase(toReturn.begin() + i);
        }
    }

    return toReturn;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots){
    // Your code here!
    V2D toReturn;

    std::unordered_map<std::string, std::vector<std::string>> rosterMap;
    for(auto &currCourse : courses) {
        std::vector<std::string> stuClassList = {currCourse.begin()+1, currCourse.end()};
        std::pair<std::string, std::vector<std::string>> toInsert (currCourse[0], stuClassList);
        rosterMap.insert(toInsert);
    }

    std::vector<std::vector<int>> adjMat {courses.size(), std::vector<int>(courses.size(), 0)};
    for(size_t i = 0; i < courses.size(); i++) {
        for(size_t j = 0; j < courses.size(); j++) {
            if(i == j) {
                continue;
            }
            if(adjMat[i][j] == 1) {
                continue;
            }
            std::unordered_map<std::string, std::vector<std::string>>::const_iterator checkFirst = rosterMap.find(courses[i][0]);
            std::unordered_map<std::string, std::vector<std::string>>::const_iterator checkSecond = rosterMap.find(courses[j][0]);
            if((checkFirst == rosterMap.end()) || (checkSecond == rosterMap.end())) {
                continue;
            }
            for(size_t toCheck = 0; toCheck < checkSecond->second.size(); toCheck++) {
                if(std::find(checkFirst->second.begin(), checkFirst->second.end(), checkSecond->second[toCheck]) != checkFirst->second.end()) {
                    adjMat[i][j] = 1;
                    adjMat[j][i] = 1;
                    continue;
                }
            }
        }
    }

    // for(size_t i = 0; i < adjMat.size(); i++) {
    //     for(size_t j = 0; j < adjMat.size(); j++) {
    //         std::cout<< adjMat[i][j];
    //         std::cout<<" ";	
    //     }
    //     std::cout<<"\n";
    // }
    // std::cout<<"Done\n";

	bool checkClass = false;
    for(int startClass = 0; startClass < static_cast<int>(adjMat.size()); startClass++) {
        checkClass = scheduleHelper(startClass, adjMat, toReturn, timeslots, courses);
		if(checkClass) {
			break;
		}
    }
	// std::cout<<"Done check class\n";

	if(checkClass) {
		return toReturn;
	} else {
		V2D notFound;
		std::vector<std::string> noSched;
		noSched.push_back("-1");
		notFound.push_back(noSched);
		return notFound;
	}
}

bool scheduleHelper(int startClass, std::vector<std::vector<int>> &adjMat, V2D &finalSchedule, const std::vector<std::string> &givenTimes, const V2D &givenCourses) {
	std::vector<int> schedTime{std::vector<int>(adjMat.size(), -1)};
	int currClass = startClass;
	for(int i = 0; i < static_cast<int>(adjMat.size()); i++) {
		int currI = i + startClass;
		if(currI >= static_cast<int>(adjMat.size())) {
				currI -= static_cast<int>(adjMat.size());
		}
		std::unordered_set<int> currTimes;
        for(int j = 0; j < static_cast<int>(adjMat.size()); j++) {
			int currJ = j;
			if(adjMat[currI][currJ] != 1) {
				continue;
			}
			if(schedTime[currJ] >= 0) {
				currTimes.insert(schedTime[currJ]);
			}
        }
		int assignTime;
		bool couldTime = false;
		for(assignTime = 0; assignTime < static_cast<int>(givenTimes.size()); assignTime++) {
			if(currTimes.insert(assignTime).second) {
				couldTime = true;
				break;
			}
		}
		if(!couldTime) {
			return false;
		}
		schedTime[currI] = assignTime;
    }

	// for(size_t k = 0; k < schedTime.size(); k++) {
	// 	std::cout<<k;
	// 	std::cout<<": ";
	// 	std::cout<<schedTime[k]<<std::endl;
	// }

	for(int slot = 0; slot < static_cast<int>(givenTimes.size()); slot++) {
		std::vector<std::string> toInsert;
		toInsert.push_back(givenTimes[slot]);
		finalSchedule.push_back(toInsert);
	}

	for(int addClass = 0; addClass < static_cast<int>(schedTime.size()); addClass++) {
		finalSchedule[schedTime[addClass]].push_back(givenCourses[addClass][0]);
	}

	return true;
}