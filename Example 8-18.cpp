
#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include <string> 

using Words = std::vector<std::shared_ptr<std::string>>;

void extract_words (const std::string& text, Words& words);
void sort_words (Words& words, size_t starting_index, size_t concluding_index);
void swap(Words& words, size_t i, size_t j);
size_t longest_word_size(const Words& words);
void show_words(const Words& words, size_t maxword_length);

int main()
{
	std::string text;
	std::cout << "Please enter some text, press * to conclude entry: " << std::endl;
	std::getline(std::cin, text, '*');
	
	Words words;
	
	extract_words(text, words);
	if (words.empty()) { std::cout << "No words to sort" << std::endl; return 0; }
	
	show_words(words, longest_word_size(words));
	
	sort_words(words, 0, words.size()-1);
	show_words(words, longest_word_size(words)); 
}
	
void extract_words (const std::string& text, Words& words)
{
	std::cout << "\nWord extraction started." << std::endl;
	const std::string separators {",.;: \t\n\\\"/?!"};
	size_t start {text.find_first_not_of(separators)};
	size_t end{};
	while (start!=std::string::npos)
	{
		end = text.find_first_of(separators, start+1);
		if (end == std::string::npos) end = text.length();
		words.push_back(std::make_shared<std::string>(text.substr(start, end-start)));
		start = text.find_first_not_of(separators, end+1);
	}
	std::cout << "\nWord extraction completed." << std::endl;
}

void sort_words (Words& words, size_t starting_index, size_t concluding_index)
{
	if (words.empty()) { std::cout << "\nWords container is empty.\n"; return; }
	if (concluding_index <= starting_index) return;
	std::cout << "\nWord sorting started." << std::endl; 
	
	swap (words, starting_index, (starting_index+concluding_index)/2);
	size_t current {starting_index};
	
	for (size_t i{starting_index+1}; i<=concluding_index; ++i) 
		if (*words.at(i) < *words.at(starting_index)) 
			swap(words, ++current, i); 
	
	swap(words, starting_index, current);
		
	if (current > starting_index) sort_words(words, starting_index, current-1);
	if (concluding_index > current+1) sort_words(words, current+1, concluding_index);
	std::cout << "\nWord sorting completed." << std::endl;
}

void swap(Words& words, size_t i, size_t j)
{
	std::shared_ptr<std::string> temp {words.at(i)};
	words.at(i) = words.at(j);
	words.at(j)=temp;
}

size_t longest_word_size(const Words& words)
{
	size_t maxword_length{};
	for (const auto& word : words) if (word->length() > maxword_length) maxword_length = word->length();
	return maxword_length;
}

void show_words(const Words& words, size_t maxword_length)
{
	if (words.empty()) { std::cout << "\nWords container is empty.\n"; return; }
	std::cout << "\nWord printing started." << std::endl;
	size_t count{};
	for (const auto& word : words) 
	{
		std::cout << std::setw(maxword_length+2) << *word;
		if (!(++count%5)) std::cout << std::endl;
	}
	std::cout << "\nWord printing ended." << std::endl;
}
	

	
		
		
	
	