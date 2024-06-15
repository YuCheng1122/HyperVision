#include <gflags/gflags.h>
#include <cstdlib>

#include "common.hpp"
#include "./graph_analyze/detector_main.hpp"

using namespace std;

DEFINE_string(config, "", "Configuration file location.");

int main(int argc, char *argv[])
{
    __START_FTIMMER__

    google::ParseCommandLineFlags(&argc, &argv, true);

    // Get the config file path from the environment variable
    const char *config_env = std::getenv("CONFIG_PATH");
    if (config_env != nullptr)
    {
        FLAGS_config = string(config_env);
    }

    if (FLAGS_config.empty())
    {
        FATAL_ERROR("Configuration file location is not specified.");
    }

    json config_j;
    try
    {
        ifstream fin(FLAGS_config, ios::in);
        fin >> config_j;
    }
    catch (const exception &e)
    {
        FATAL_ERROR(e.what());
    }

    auto hv1 = make_shared<Hypervision::hypervision_detector>();
    hv1->config_via_json(config_j);
    hv1->start();

    __STOP_FTIMER__
    __PRINTF_EXE_TIME__

    return 0;
}
