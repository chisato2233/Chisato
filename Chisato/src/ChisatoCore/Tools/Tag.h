#pragma once
#include <any>


namespace cst {
    using tag_id_t = uint64_t;

    struct CSTAPI tag_tree_node {
        tag_id_t value = -1;
        tag_tree_node* parent = nullptr;
        std::vector<std::shared_ptr<tag_tree_node>> children{};

        std::string comment{};
        std::any data = nullptr;

        
        tag_tree_node() = default;
        tag_tree_node(tag_id_t val, tag_tree_node* par)
            : value(val), parent(par){}
    };

    struct CSTAPI tag_system {
        static void init() {
            root = std::make_shared<tag_tree_node>(0, nullptr);
            tag_dict[0] = root_tag_symbol;
            tag_count = 1;
            register_tag("cst::a", "", 1);
        }

        static tag_id_t register_tag(std::string_view tag_str,std::string_view comment = "",std::any data = std::any{}) {
            auto tags = parse_tag(tag_str);
            auto current_node = root;


            for (const auto& tag : tags) {
            	if (tag == null_tag_symbol) { return -1; }


                auto it = std::ranges::find_if(current_node->children, [&tag](const std::shared_ptr<tag_tree_node>& node) {
                    if (auto it = tag_dict.find(node->value);it!=tag_dict.end()) 
						return it->second == tag;
					else  return false;
                });

                if (it == current_node->children.end()) {
                    auto new_node = std::make_shared<tag_tree_node>(tag_count++, current_node.get());
                    new_node->comment = comment;
                    new_node->data = data;
					tag_dict[new_node->value] = tag;
                    current_node->children.push_back(new_node);
                    current_node = new_node;
                }
                else {
                    current_node = *it;
                }
            }
            return current_node->value;
        }

		//parse tag will delete the root tag symbol;
        static std::vector<std::string> parse_tag(std::string_view tag_str) {
            std::vector<std::string> result;
            size_t start = 0;
            size_t end = tag_str.find(split_symbol);

            while (end != std::string::npos) {
                if (end > start) {
                    result.emplace_back(tag_str.substr(start, end - start));
                }
                start = end + split_symbol.length();
                end = tag_str.find(split_symbol, start);
            }

            if (start < tag_str.size()) {
                result.emplace_back(tag_str.substr(start));
            }
			if (!result.empty() && result[0] == root_tag_symbol) result.erase(result.begin());
            return result;
        }

        static tag_id_t find_tag(std::string_view tag_str) {
            auto tags = parse_tag(tag_str);
            auto current_node = root;

            for (const auto& tag : tags) {
                auto it = std::ranges::find_if(current_node->children,[&tag](const std::shared_ptr<tag_tree_node>& node) {
                    if (auto it = tag_dict.find(node->value); it != tag_dict.end())
                        return it->second == tag;
                    else  return false;
                });

                if (it == current_node->children.end()) {
                    return -1; // Tag not found
                }
                else {
                    current_node = *it;
                }
            }

            return current_node->value;
        }

        static tag_tree_node* find_tag_in_tree(std::string_view tag_str) {
			auto tags = parse_tag(tag_str);
			auto current_node = root.get();

			for (const auto& tag : tags) {
				auto it = std::ranges::find_if(current_node->children, [&tag](const std::shared_ptr<tag_tree_node>& node) {
					if (auto it = tag_dict.find(node->value); it != tag_dict.end())
						return it->second == tag;
					else  return false;
				});

				if (it == current_node->children.end()) {
					return nullptr; // Tag not found
				}
				else {
					current_node = it->get();
				}
			}

			return current_node;
        }

        static bool add_tag_comment() {
            return false;
        }
        static bool add_tag_data() {
            return false;
        }


        static std::string tag_tree_str() {
            std::ostringstream oss;
            oss << "\n";
            tag_tree_str_helper(root, "", true, oss);
            return oss.str();
        }

		static std::string find_common_parent(std::string_view lhs, std::string_view rhs) {
            if (lhs == tag_system::root_tag_symbol || rhs == tag_system::root_tag_symbol) {
                return tag_system::root_tag_symbol ;
            }
            else if (lhs == tag_system::null_tag_symbol || rhs == tag_system::null_tag_symbol) {
                return  tag_system::null_tag_symbol ;
            }


            const auto lhs_parts = tag_system::parse_tag(lhs);
            const auto rhs_parts = tag_system::parse_tag(rhs);

            const size_t min_size = min(lhs_parts.size(), rhs_parts.size());
            size_t common_length = 0;

            for (size_t i = 0; i < min_size; ++i) {
                if (lhs_parts[i] == rhs_parts[i]) {
                    common_length++;
                }
                else {
                    break;
                }
            }

            if (common_length == 0) {
                return  tag_system::root_tag_symbol ;
            }

            std::string common_full_name = lhs_parts[0];
            for (size_t i = 1; i < common_length; ++i) {
                common_full_name += tag_system::split_symbol + lhs_parts[i];
            }

            return common_full_name ;
		}

        static std::string try_find_parent(std::string tag_str) {
            if (tag_str == tag_system::root_tag_symbol || tag_str == tag_system::null_tag_symbol) {
                return  "" ;
            }

            auto pos = tag_str.rfind(tag_system::split_symbol);
            if (pos == std::string::npos) {
                return  tag_system::root_tag_symbol ;
            }

            return tag_str.substr(0, pos) ;
        }

		

        static bool check_contain_tag(const std::string& a,const std::string& b) {
            return a.find(b) != std::string::npos;
        }



        inline static std::unordered_map<tag_id_t, std::string> tag_dict;
        inline static std::string split_symbol = "::";
        inline static std::string root_tag_symbol = "@";
        inline static std::string null_tag_symbol = "~";
        inline static tag_id_t tag_count = 0;

    private:
        static void tag_tree_str_helper(const std::shared_ptr<tag_tree_node>& node, const std::string& prefix, bool is_last, std::ostringstream& oss) {
            if (!node) return;

            oss << prefix;

            if (prefix.empty()) {
                oss << "    ";
            }
            else {
                oss << (is_last ? "└── " : "├── ");
            }

            oss << (tag_dict.find(node->value) != tag_dict.end() ? tag_dict[node->value] : "N/A") << "\n";

            for (size_t i = 0; i < node->children.size(); ++i) {
                tag_tree_str_helper(node->children[i], prefix + (is_last ? "    " : "│   "), i == node->children.size() - 1, oss);
            }
        }
        inline static std::shared_ptr<tag_tree_node> root;
    };

    template<size_t N>
    struct template_str {
		constexpr template_str(const char(&data)[N]) : data(data) {}
		char data[N];
    };


    struct CSTAPI tag {
        static tag create(const std::string& full_name,std::string_view comment = "",std::any data= nullptr) {
            tag_system::register_tag(full_name, comment, data);
            return tag{ full_name };
        }

    	template<typename... Strs> requires requires(Strs...) { (std::convertible_to<Strs, std::string> && ...); }
        static tag create(const Strs&... strings) {
            std::string full_name = ((std::string(strings) + tag_system::split_symbol) + ...);
            if (!full_name.empty()) {
                full_name.resize(full_name.size() - tag_system::split_symbol.size()); // Remove the trailing split_symbol
            }
            return create(full_name);
    	}

        

        template<typename... Strs> requires requires(Strs...) { (std::convertible_to<Strs, std::string> && ...); }
		static tag create(const tag& parent, const Strs&... strings) {
			return create(parent.full_name,strings...);
    	}

		//add a child to this tag
        tag& add_child(const std::string& child) { create(*this, child); return *this; }


		//add multiple children to this tag
    	template<typename... Strs> requires requires(Strs...) { (std::convertible_to<Strs, std::string> && ...); }
        tag& add_childrend(const Strs&... strings) { (create(*this, strings), ...); return *this; }

        //add comment
        tag& add_comment(const std::string& comment) {
			auto node = tag_system::find_tag_in_tree(full_name);
			if (node) {
				node->comment = comment;
			}
			return *this;
        }

        //add data
        tag& add_data(std::any data) {
	        auto node = tag_system::find_tag_in_tree(full_name);
            if (node) node->data = data;
            return *this;
        }




		//return the parent of this tag
        tag parent() const { return tag{ tag_system::try_find_parent(full_name) }; }

        //return the children of this tag
		std::vector<tag> children()const {
			auto node = tag_system::find_tag_in_tree(full_name);
			if (!node) return {};
			std::vector<tag> result;
			for (const auto& child : node->children) {
				result.push_back(tag{ tag_system::tag_dict[child->value] });
			}
			return result;
		}

        tag find_child(const std::string& child_str) const {
	        const auto node = tag_system::find_tag_in_tree(full_name + tag_system::split_symbol + child_str);
			return tag{ node ? tag_system::tag_dict[node->value] : tag_system::null_tag_symbol};
        }

        //get comment
        std::string get_comment()const { return tag_system::find_tag_in_tree(full_name)->comment; }

        //get data
        std::any get_data()const { return tag_system::find_tag_in_tree(full_name)->data; }

    	//check if this tag contain the other tag
        bool contain(const tag& other) const { return tag_system::check_contain_tag(full_name, other.to_string()); }

		//find the common parent of two tags
    	friend tag operator^(const tag& lhs, const tag& rhs) {
			return tag{ tag_system::find_common_parent(lhs.full_name, rhs.full_name) };
        }

		friend std::ostream& operator<<(std::ostream& os, const tag& tag) {
			os << tag.full_name;
			return os;
		}

		friend bool operator==(const tag& lhs, const tag& rhs) {
			return lhs.full_name == rhs.full_name;
		}


        std::string to_string() const { return full_name; }
        operator std::string() const { return full_name; }
        operator bool()const { return full_name != tag_system::null_tag_symbol; }
		tag operator/(const std::string& other) {
            if (auto child = find_child(other); child) 
                return child;
        	add_child(other);
        	return find_child(other);
		}


    private:
        tag() = default;
		tag(const std::basic_string<char>& full_name) : full_name(full_name) {}
        std::string full_name;
    };

}



template<>
struct std::hash<cst::tag> :std::hash<std::string> {
	size_t operator()(const cst::tag& tag) const noexcept {
		return std::hash<std::string>::operator()(tag.to_string());
	}
};


