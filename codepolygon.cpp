#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Point structure to store polygon vertices
struct Point {
    double x, y;
};

// Generate a simple polygon without self-intersections
std::vector<Point> generatePolygon(int num_points, double radius = 10.0) {
    std::vector<Point> points;
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.8, 1.0);

    for (int i = 0; i < num_points; i++) {
        double angle = 2 * M_PI * i / num_points;
        double r = distribution(generator) * radius;
        points.push_back({ r * cos(angle), r * sin(angle) });
    }

    // Calculate centroid
    Point centroid = { 0.0, 0.0 };
    for (const auto& p : points) {
        centroid.x += p.x;
        centroid.y += p.y;
    }
    centroid.x /= num_points;
    centroid.y /= num_points;

    // Sort points by angle from centroid
    std::sort(points.begin(), points.end(), [&centroid](const Point& a, const Point& b) {
        return atan2(a.y - centroid.y, a.x - centroid.x) < atan2(b.y - centroid.y, b.x - centroid.x);
        });

    return points;
}

// Shoelace formula for calculating area
double shoelaceArea(const std::vector<Point>& points) {
    double area = 0.0;
    int n = points.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += points[i].x * points[j].y - points[j].x * points[i].y;
    }
    return std::abs(area) / 2.0;
}

// Monte Carlo method for area estimation
double monteCarloArea(const std::vector<Point>& points, int num_points = 10000) {
    // Find bounding box
    double min_x = points[0].x, max_x = points[0].x;
    double min_y = points[0].y, max_y = points[0].y;
    for (const auto& p : points) {
        min_x = std::min(min_x, p.x);
        max_x = std::max(max_x, p.x);
        min_y = std::min(min_y, p.y);
        max_y = std::max(max_y, p.y);
    }

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution_x(min_x, max_x);
    std::uniform_real_distribution<double> distribution_y(min_y, max_y);

    int inside_count = 0;
    for (int i = 0; i < num_points; i++) {
        Point random_point = { distribution_x(generator), distribution_y(generator) };
        bool inside = false;

        // Check if the random point is inside the polygon using ray-casting
        for (int j = 0, k = points.size() - 1; j < points.size(); k = j++) {
            if (((points[j].y > random_point.y) != (points[k].y > random_point.y)) &&
                (random_point.x < (points[k].x - points[j].x) * (random_point.y - points[j].y) /
                    (points[k].y - points[j].y) + points[j].x)) {
                inside = !inside;
            }
        }

        if (inside) inside_count++;
    }

    double box_area = (max_x - min_x) * (max_y - min_y);
    return box_area * (static_cast<double>(inside_count) / num_points);
}

// Benchmarking function for execution time
void benchmarkAreaCalculations(const std::vector<Point>& points) {
    auto start = std::chrono::high_resolution_clock::now();
    double shapely_area = shoelaceArea(points);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> shoelace_duration = end - start;
    std::cout << "Shoelace Area: " << shapely_area << " (Time: " << shoelace_duration.count() << " seconds)" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    double mc_area = monteCarloArea(points);
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> monte_carlo_duration = end - start;
    std::cout << "Monte Carlo Area (10,000 points): " << mc_area << " (Time: " << monte_carlo_duration.count() << " seconds)" << std::endl;
}

// Main function to perform tasks for each polygon size
int main() {
    std::vector<int> vertex_counts = { 10, 50, 100 };

    for (int n : vertex_counts) {
        std::cout << "\nPolygon with " << n << " vertices:" << std::endl;
        auto polygon = generatePolygon(n);

        // Shoelace formula area calculation
        double area_shoelace = shoelaceArea(polygon);
        std::cout << "Shoelace Area: " << area_shoelace << std::endl;

        // Monte Carlo method area calculation with initial points
        double area_mc = monteCarloArea(polygon, 10000);
        std::cout << "Monte Carlo Area (10,000 points): " << area_mc << std::endl;

        // Benchmarking execution times
        benchmarkAreaCalculations(polygon);
    }

    return 0;
}
