/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <unordered_set>

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
    std::string text = file_to_string(filename);
    std::vector<std::string> lines;
    int n = SplitString(text, '\n', lines);
    V2D ret = std::vector<std::vector<std::string>>(n, std::vector<std::string>(0));
    for (int i = 0; i < n; ++ i) {
        std::vector<std::string> line;
        int m = SplitString(lines[i], ',', line);
        for (int j = 0; j < m; ++ j)
            ret[i].push_back(Trim(line[j]));
    }
    return ret;
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
    V2D ret = cv;
    std::unordered_map<std::string, std::unordered_set<std::string>> m;
    for (auto& it : student) 
        for (unsigned i = 1; i < it.size(); ++ i) 
            m[it[0]].insert(it[i]);

    for (auto& it : ret) 
        for (unsigned i = 1; i < it.size(); ) 
            if (m[it[i]].count(it[0])) i ++ ;
            else it.erase(it.begin() + i);

    for (unsigned i = 0; i < ret.size(); ) 
        if (ret[i].size() != 1) i ++ ;
        else ret.erase(ret.begin() + i);
    
    return ret;
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
    Graph g;
    std::unordered_map<std::string, std::unordered_set<std::string>> m;
    for (auto it : courses)
        for (unsigned i = 1; i < it.size(); ++ i)
            m[it[i]].insert(it[0]);
    
    for (auto it : courses) {
        g.add(it[0]);
        for (unsigned i = 1; i < it.size(); ++ i)
            for (auto j : m[it[i]])
                if (j != it[0])
                    g.add(it[0], j);
    }

    auto v = g.get_vertices();
    do {
        if (g.schedule(v) <= timeslots.size()) {
            V2D ret = std::vector<std::vector<std::string>>(timeslots.size(), std::vector<std::string>(0));
            for (unsigned i = 0; i < timeslots.size(); ++ i) 
                ret[i].push_back(timeslots[i]);
            for (auto t : g.color) {
                ret[t.second - 1].push_back(t.first);
            }
            return ret;
        }
    } while (std::next_permutation(v.begin(), v.end()));
    
    return std::vector<std::vector<std::string>>(1, std::vector<std::string>(1, "-1"));
}