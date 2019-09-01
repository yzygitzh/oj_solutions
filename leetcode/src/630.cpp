class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(), courses.end(),
             [] (const vector<int>& a, const vector<int>& b) {
                 return a[1] < b[1];
             });
        priority_queue<int> optimalCourses;
        int totalDays = 0;
        for (auto& course : courses) {
            int days = course[0];
            int deadline = course[1];
            if (totalDays + days <= deadline) {
                optimalCourses.push(days);
                totalDays += days;
            } else if (!optimalCourses.empty() &&
                       days < optimalCourses.top() &&
                       totalDays - optimalCourses.top() + days <= deadline) {
                totalDays -= optimalCourses.top();
                optimalCourses.pop();
                optimalCourses.push(days);
                totalDays += days;
            }
        }
        return optimalCourses.size();
    }
};