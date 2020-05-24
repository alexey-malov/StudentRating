#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>


struct Student
{
	std::string name;
	std::vector<int> scores;
};

double GetAverageScore(const Student& student)
{
	if (student.scores.empty())
	{
		return 0.0;
	}
	double totalScore = std::accumulate(student.scores.begin(), student.scores.end(), 0);
	return totalScore / student.scores.size();
}

void SortStudentsByAverageScore(std::vector<Student>& students)
{
	std::sort(students.begin(), students.end(), [](const Student& s1, const Student& s2) {
		double student1AverageScore = GetAverageScore(s1);
		double student2AverageScore = GetAverageScore(s1);
		if (student1AverageScore == student2AverageScore)
		{
			return s1.name < s2.name;
		}
		else
		{
			return student1AverageScore > student2AverageScore;
		}
	});
}

std::vector<Student> FindAllSucceededStudents(const std::vector<Student>& students, double averageScoreThreshold)
{
	std::vector<Student> succeededStudents;

	auto isSucceeded = [averageScoreThreshold](const Student& student) {
		return GetAverageScore(student) >= averageScoreThreshold;
	};
	std::copy_if(students.begin(), students.end(), std::back_inserter(succeededStudents), isSucceeded);

	return succeededStudents;
}

void PrintStudents(const std::vector<Student>& students, std::ostream& output)
{
	std::for_each(students.begin(), students.end(), [&output](const Student& student) {
		output << student.name << " (" << GetAverageScore(student) << ")\n";
	});
}

std::vector<Student> ReadStudents(unsigned count, std::istream& input)
{
	using namespace std;

	vector<Student> students;
	
	while (count-- != 0)
	{
		Student student;
		unsigned numberOfScores;

		input >> student.name >> numberOfScores;
		student.scores.reserve(numberOfScores);
		if (numberOfScores != 0)
		{
			copy_n(istream_iterator<int>(input), numberOfScores, back_inserter(student.scores));
		}
		students.emplace_back(std::move(student));
	}

	return students;
}

int main()
{
	unsigned numberOfStudents;
	double successThreshold;
	
	std::cin >> numberOfStudents >> successThreshold;
	
	auto students = ReadStudents(numberOfStudents, std::cin);
	auto succeededStudents = FindAllSucceededStudents(students, successThreshold);
	
	SortStudentsByAverageScore(succeededStudents);
	
	PrintStudents(succeededStudents, std::cout);

	return 0;
}
