#pragma once

#include "lve_model.hpp"

// std 
#include <vector>

class SierpinskiTriangle{
public:
	static std::vector<lve::LveModel::Vertex> solution(std::vector<lve::LveModel::Vertex> vertices);
private:
	static lve::LveModel::Vertex findMiddle(lve::LveModel::Vertex vertice1, lve::LveModel::Vertex vertice2);
};