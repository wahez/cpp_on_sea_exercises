#include <random>
#include <unordered_set>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

inline std::vector<std::string> read_lines(const char* path)
{
	std::vector<std::string> out;
	std::ifstream input(path);
	std::string line;
	while(std::getline(input, line))
	{
		out.push_back(line);
	}
	return out;
}

inline std::string read_full_file(const char* path)
{
	std::ifstream input(path);
	std::ostringstream os;
	os << input.rdbuf();
	return os.str();
}

inline std::string CreateRandomString()
{
    static std::random_device rd;
    static std::uniform_int_distribution<int> charDist(48, 127);
    static std::lognormal_distribution<float> lengthDist(2.19, 0.25);
    std::size_t len = (int)(std::floor(lengthDist(rd))) + 1;
    std::string out;
    out.reserve(len);
    for(std::size_t i = 0; i < len; i++)
        out.push_back(charDist(rd));

    return out;
}

inline std::vector<std::string> CreateUniqueRandomStrings(std::size_t len)
{
    std::unordered_set<std::string> strings;
    strings.reserve(len);

    while (strings.size() < len)
        strings.insert(CreateRandomString());

    return std::vector<std::string>(strings.begin(), strings.end());
}

//papi::event_set<PAPI_TOT_INS, PAPI_TOT_CYC, PAPI_BR_MSP, PAPI_L1_DCM> events;
//papi::event_set<PAPI_L1_TCM, PAPI_L2_TCM, PAPI_L3_TCM> events;
//events.start_counters();
//events.stop_counters();

//std::cout << "l1 cache misse per iteration: " << events.get<PAPI_L1_TCM>().counter() / double(state.iterations()) << std::endl;
//std::cout << "l2 cache misse per iteration: " << events.get<PAPI_L2_TCM>().counter() / double(state.iterations()) << std::endl;
//std::cout << "l3 cache misse per iteration: " << events.get<PAPI_L3_TCM>().counter() / double(state.iterations()) << std::endl;

//std::cout << events.get<PAPI_TOT_INS>().counter()/double(events.get<PAPI_TOT_CYC>().counter()) << " instr per cycle\n";
//std::cout << events.get<PAPI_TOT_INS>().counter()/double(state.iterations()) << " instructions\n";
//std::cout << events.get<PAPI_L1_DCM>().counter()/double(state.iterations()) << " l1 cache misses\n"
//          << events.get<PAPI_BR_MSP>().counter()/double(state.iterations()) << " branch misses" << std::endl;
//std::cout << "iterations: " << state.iterations() << std::endl;


//CALLGRIND_START_INSTRUMENTATION;
//CALLGRIND_STOP_INSTRUMENTATION;
