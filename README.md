# PolygonWorkBench

Objectives 
-	Get familiar with different methods for calculating the area of polygons. 
-	Use both library-based and custom implementations to calculate the area of polygons. 
-	Investigate the computational load depending on the accuracy and complexity of the polygon. 
-	Compare the efficiency and accuracy of different approaches based on experimental data. 

Theoretical Information:

Gauss's Formula 
The area of a polygon on a plane can be calculated using the polygon area formula, also known as Gauss's formula or the shoelace formula: 

![image](https://github.com/user-attachments/assets/0cb3b6ae-9c13-4e93-b38b-74d1aecac864)

where:

![image](https://github.com/user-attachments/assets/06b9b12d-94fe-4de8-b046-f40f915a3dc2) — the coordinates of the polygon's vertices,

![image](https://github.com/user-attachments/assets/9931ba8c-023c-47cd-919b-6dfded97e152) — the number of vertices.
This formula is used to calculate the area of polygons with known vertex coordinates. It works for any polygon, regardless of whether it is convex or has a complex shape.

Monte Carlo Method

The Monte Carlo method is a statistical approach that can be used to estimate the area of complex shapes when calculating an analytical formula is difficult or impossible. The essence of the method is to randomly scatter points within a bounding rectangle and calculate the proportion of points that fall inside the polygon.

Monte Carlo Method Algorithm: 
-	Define the rectangle that bounds the polygon. 
-	Randomly scatter points within this rectangle. 
-	Calculate the proportion of points that fall inside the polygon. 
-	Estimate the area of the polygon by multiplying the proportion by the area of the rectangle. 

# Main Task

1)	Polygon Initialization: 
-	Generate a polygon without self-intersections with specified numbers of vertices: 10, 50, and 100. 
-	Use the provided code to generate a simple closed polygon. 
2)	Polygon Area Calculation: 
-	Use the library-based method with Shapely. 
-	Implement the Gauss method (Shoelace formula). 
-	Implement the Monte Carlo method for area estimation. 
3)	Accuracy and Performance Investigation: 
-	For the Monte Carlo method: 
1.	Set an acceptable accuracy (e.g., 1% error). 
2.	Find the minimum number of iterations required to achieve this accuracy. 
-	Benchmark each method for polygons with 10, 50, and 100 vertices. 
-	Measure execution time for each method and analyze the performance based on the number of vertices. 
4)	Data Collection and Analysis: 
-	Record the results of the experiments in tables. 
-	Plot graphs showing the dependency of execution time on the number of points and Monte Carlo iterations. 
-	Analyze the results and draw conclusions about the efficiency of the methods.

Solution:

