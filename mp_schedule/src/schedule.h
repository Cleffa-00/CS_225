/**
 * @file schedule.h
 * Exam scheduling using graph coloring
 */

#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <set>
#include <unordered_set>
#include <algorithm>

typedef std::vector<std::vector<std::string> > V2D; 


/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. You must preserve the order from the input file.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 * @return The vector of vectors of strings imported from filename
 */
V2D file_to_V2D(const std::string & filename);

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param course A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 * @return A 2D vector of strings where each row is a course followed by all the students in the course
 */
V2D clean(const V2D & cv, const V2D & sv);

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * If a valid solution cannot be formed after <XXX: How many iterations?> iterations of graph coloring, return a V2D with one row
 * with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 * @return A 2D vector which each row is a timeslot with all the courses scheduled for that time
 */
V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots);

class Graph {
    private:
        int idx = 0;
        unsigned max_color = 0;
        std::unordered_map<std::string, int> h;
        std::unordered_map<int, std::string> e;
        std::unordered_map<int, int> ne;
        std::unordered_map<std::string, std::unordered_set<int>> st;
    public:
        std::unordered_map<std::string, int> color;
        Graph() = default;
        void add(std::string a, std::string b) { e[ ++ idx] = b, ne[idx] = h[a], h[a] = idx; }
        void add(std::string a) { h[a] = 0; }

        void dfs(std::string u, unsigned c) {
            while (st[u].count(c)) c ++ ;
            color[u] = c;
            if (c > max_color) max_color = c;
            for (int i = h[u]; i != 0; i = ne[i]) {
                st[e[i]].insert(c);
            }
        }

        std::vector<std::string> get_vertices() {
            std::vector<std::string> v;
            for (auto i : h) v.push_back(i.first);
            std::sort(v.begin(), v.end());
            return v;
        }
        
        unsigned schedule(std::vector<std::string>& v) {
            max_color = 0;
            st.clear();
            color.clear();
            for (auto x : v) dfs(x, 1);
            return max_color;
        }
};