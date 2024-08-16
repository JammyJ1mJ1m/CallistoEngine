#include "DiscordManager.h"

void DiscordManager::initDiscord()
{
    DiscordEventHandlers handlers;
    memset(&handlers, 0, sizeof(handlers));
    handlers.ready = [](const DiscordUser* connectedUser) {
        std::cout << "Discord: connected to user " << connectedUser->username << "#" << connectedUser->discriminator << std::endl;
        };
    handlers.errored = [](int errorCode, const char* message) {
        std::cerr << "Discord: error (" << errorCode << "): " << message << std::endl;
        };
    handlers.disconnected = [](int errorCode, const char* message) {
        std::cerr << "Discord: disconnected (" << errorCode << "): " << message << std::endl;
        };

    Discord_Initialize("1230226002119233650", &handlers, 1, nullptr);

    // current default presence
    SetDiscordPresence("Making game", "In Game", "cglarge", "AAAA", "asset1", "Look at his smile");
}

void DiscordManager::UpdateDiscordPresence()
{
    Discord_RunCallbacks();
}

void DiscordManager::SetDiscordPresence(const char* details, const char* state, const char* largeImageKey, const char* largeImageText, const char* smallImageKey, const char* smallImageText)
{
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.state = state; // The user's current state
    discordPresence.details = details; // The details of the activity
    discordPresence.largeImageKey = largeImageKey; // Key name of the large image asset
    discordPresence.largeImageText = largeImageText; // Tooltip for the large image
    discordPresence.smallImageKey = smallImageKey; // Key name of the small image asset
    discordPresence.smallImageText = smallImageText; // Tooltip for the small image
    UpdatePresence(discordPresence);
}

void DiscordManager::SetDiscordPresence(const char* details, const char* state)
{
    SetDiscordPresence(details, state, "cglarge", "AAAA", "asset1", "Look at his smile");
}

void DiscordManager::SetDiscordPresence(std::string& details, std::string& state, std::string& largeImageKey, std::string& largeImageText, std::string& smallImageKey, std::string& smallImageText)
{
    SetDiscordPresence(details.c_str(), state.c_str(), largeImageKey.c_str(), largeImageText.c_str(), smallImageKey.c_str(), smallImageText.c_str());
}

void DiscordManager::SetDiscordPresence(const char* details, const int state)
{
    SetDiscordPresence(details, std::to_string(state).c_str(), "cglarge", "AAAA", "asset1", "Look at his smile");
}

void DiscordManager::SetDiscordPresence(std::string& details, std::string& state)
{
    SetDiscordPresence(details.c_str(), state.c_str(), "cglarge", "AAAA", "asset1", "Look at his smile");
}

void DiscordManager::UpdatePresence(DiscordRichPresence& pPresence)
{
    Discord_UpdatePresence(&pPresence);
}