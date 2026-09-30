#include <SKSE/SKSE.h>
#include <spdlog/sinks/basic_file_sink.h>

SKSEPluginLoad(const SKSE::LoadInterface *skse) {
  SKSE::Init(skse);
  auto logger = spdlog::basic_logger_mt("global", "MyPlugin.log", true);
  spdlog::set_default_logger(logger);
  logger->info("Hello from Linux-built plugin!");
  return true;
}