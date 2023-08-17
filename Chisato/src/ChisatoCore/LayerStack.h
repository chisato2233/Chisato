#pragma once
#include"Layer.h"

namespace Chisato {
	class CSTAPI LayerStack {
		std::vector<std::shared_ptr<Layer>> layerVec;
		std::vector<std::shared_ptr<Layer>>::iterator stackTop=layerVec.begin();

	public:
		auto begin() { return layerVec.begin(); }
		auto end() { return layerVec.end(); }


		void push(const std::shared_ptr<Layer>& layer) { stackTop = layerVec.emplace(stackTop, layer); }
		void push_over(const std::shared_ptr<Layer>& layer) { layerVec.emplace_back(layer); }

		void pop() { layerVec.erase(stackTop--); }
		void pop_over() {
			if (stackTop == layerVec.end() - 1) pop();
			else layerVec.pop_back();
		}

		void erase(const std::shared_ptr<Layer>& layer) {
			const auto i = std::ranges::find(layerVec, layer);
			if (i != layerVec.end()) {
				layerVec.erase(i);
				--stackTop;
			}
		}
	};
}