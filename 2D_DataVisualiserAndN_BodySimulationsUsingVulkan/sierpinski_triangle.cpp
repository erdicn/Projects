#include "sierpinski_triangle.hpp"

// std
#include <vector>
#include <iostream>
#include <stdexcept>

//std::vector<lve::LveModel::Vertex> vertices{
//		{{0.0f, -0.5f}},
//		{{0.5f, 0.5f}},
//		{{-0.5f, 0.5f}}
//};

std::vector<lve::LveModel::Vertex> SierpinskiTriangle::solution(std::vector<lve::LveModel::Vertex> vertices) {
	if (vertices.size() == 0) {
		std::cerr << "there are no values in vertices" << std::endl;
		throw std::runtime_error("there are no values in vertices");
	}

	std::vector<lve::LveModel::Vertex> newVertices;
	lve::LveModel::Vertex temp = vertices.at(0);
	/*for (lve::LveModel::Vertex vertice : vertices) {
	}*/
	for (int i = 1; i < vertices.size(); i++) {
		newVertices.push_back(findMiddle(temp, vertices.at(i)));
	}
	newVertices.push_back(findMiddle(vertices.at(0), vertices.back()));

	return newVertices;
}


lve::LveModel::Vertex SierpinskiTriangle::findMiddle(lve::LveModel::Vertex vertice1, lve::LveModel::Vertex vertice2) {
	return { { (vertice1.position.x + vertice2.position.x) / 2.0 ,  
					(vertice1.position.y + vertice2.position.y) / 2.0} };
}
