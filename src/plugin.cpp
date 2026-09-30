#include "logger.h"

void OnDataLoaded() {
  // USING FORMS
  // looking up via formID
  int formId = 0x64B3D;
  auto *form = RE::TESForm::LookupByID(formId);
  auto value = form->GetGoldValue();
  auto name = form->GetName();
  logger::info("The form with id {:x} is called {}, and has a gold value of {}",
               formId, name, value);

  // note - RE:: is typically for functions from commonlib, whereas SKSE:: is
  // for functions from SKSE.

  // Look up via formID as an actor pointer, as opposed to a form pointer. This
  // will allow us to access actor-specific functions and data.
  auto *marcurioBase =
      RE::TESForm::LookupByEditorID<RE::TESNPC>("HirelingMarcurio");
  auto *spells = marcurioBase->GetSpellList();
  logger::info("{} has {} spells", marcurioBase->GetName(), spells->numSpells);
  for (unsigned int i = 0; i < spells->numSpells; i++) {
    auto spell = spells->spells[i];
    logger::info("{}", spell->GetName());
  }

  // Get at alchemyitem effects
  auto sweetRoll =
      RE::TESForm::LookupByEditorID<RE::AlchemyItem>("FoodSweetRoll");
  logger::info("{} form type {}", sweetRoll->GetName(),
               sweetRoll->GetFormType());
  logger::info("{} has {} effects", sweetRoll->GetName(),
               sweetRoll->effects.size());
  for (auto *effect : sweetRoll->effects) {
    logger::info("effect: {}", effect->baseEffect->GetName());
  }

  // Get all alchemy items
  auto &alchemyItems =
      RE::TESDataHandler::GetSingleton()->GetFormArray<RE::AlchemyItem>();
  logger::info("there are {} alchemy items", alchemyItems.size());
  for (auto *item : alchemyItems) {
    if (item->fullName.contains("soup")) {
      logger::info("soup: {}", item->GetName());
    }
  }

  // Get every form in the game - returns a map from the ID of the form to the
  // pointer of the form. This is a very expensive call, so be careful when
  // using it.
  const auto &[litterallyEveryFormInTheGame, lock] = RE::TESForm::GetAllForms();
  for (auto &[id, form] : *litterallyEveryFormInTheGame) {
    if (form->IsArmor())
      if (form->GetGoldValue() >= 5000)
        logger::info("Geez, Louise. {} is v giving very much expensive at {} "
                     "gold, booboo.",
                     form->GetName(), form->GetGoldValue());
  }
}

void OnMessage(SKSE::MessagingInterface::Message *message) {
  logger::info("Message Type: {}", message->type);

  if (message->type == SKSE::MessagingInterface::kNewGame)
    logger::info("A new game has been started!");
  else if (message->type == SKSE::MessagingInterface::kSaveGame)
    logger::info("save game");
  else if (message->type == SKSE::MessagingInterface::kPostLoad)
    logger::info("SKSE has finished loading, and all plugins have loaded");
  else if (message->type == SKSE::MessagingInterface::kPostPostLoad)
    logger::info("All plugins have loaded, and now it is safe to use listeners "
                 "from other plugins");
  else if (message->type == SKSE::MessagingInterface::kPreLoadGame)
    logger::info("A save game is being loaded. file: {}",
                 (const char *)message->data);
  else if (message->type == SKSE::MessagingInterface::kPostLoadGame)
    logger::info("A save game has finished loading. Loaded ok? {}",
                 (bool)message->data);
  else if (message->type == SKSE::MessagingInterface::kDeleteGame)
    logger::info("A save game has been deleted");
  else if (message->type == SKSE::MessagingInterface::kInputLoaded)
    logger::info("SKSE's input system has finished loading");
  else if (message->type == SKSE::MessagingInterface::kDataLoaded) {
    logger::info("The game has loaded all forms");
    RE::ConsoleLog::GetSingleton()->Print(
        "The game console is ready to use! Hello World!");
    OnDataLoaded();
  }
}

SKSEPluginLoad(const SKSE::LoadInterface *skse) {
  SKSE::Init(skse);
  SetupLog();

  // LOGGING
  // set log level
  spdlog::set_level(spdlog::level::info);

  // log levels in order:
  logger::trace("for logging out every mundane thing");
  logger::debug("for logging slightly more important things");
  logger::info("logging helpful information");
  logger::warn("warnings");
  logger::error("something is broken");
  logger::critical("typically right before a crash");

  // formating log strings
  auto formId = 0x123456;
  auto text = "Sweet Roll";
  auto number = 69;

  logger::info("The text is \"{}\"", text);
  logger::info("The number is {}", number);
  logger::info(
      "The formId is {:x}, and decimal: {}", formId,
      formId); // :x will tell the code to print the formId as hexadecimal

  // LISTENING FOR EVENTS
  SKSE::GetMessagingInterface()->RegisterListener(OnMessage);

  return true;
}