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

   // DiscordRichPresence discordPresence;
   // memset(&discordPresence, 0, sizeof(discordPresence));
   // discordPresence.state = "In Game"; // The user's current state
   // discordPresence.details = "Making game"; // The details of the activity
   // discordPresence.largeImageKey = "cglarge"; // Key name of the large image asset
   // discordPresence.largeImageText = "AAAA"; // Tooltip for the large image
   // discordPresence.smallImageKey = "asset1"; // Key name of the small image asset
   // discordPresence.smallImageText = "Look at his smile"; // Tooltip for the small image
   //// discordPresence.partySize = 1; // Current size of the user's party
   //// discordPresence.partyMax = 1; // Maximum size of the user's party
    SetDiscordPresence("Making game", "In Game", "cglarge", "AAAA", "asset1", "Look at his smile");

}

void DiscordManager::UpdateDiscordPresence()
{
    Discord_RunCallbacks();
}

void DiscordManager::SetDiscordPresence(std::string& details, std::string& state, std::string& largeImageKey, std::string& largeImageText, std::string& smallImageKey, std::string& smallImageText)
{
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.state = state.c_str(); // The user's current state
    discordPresence.details = details.c_str(); // The details of the activity
    discordPresence.largeImageKey = largeImageKey.c_str(); // Key name of the large image asset
    discordPresence.largeImageText = largeImageText.c_str(); // Tooltip for the large image
    discordPresence.smallImageKey = smallImageKey.c_str(); // Key name of the small image asset
    discordPresence.smallImageText = smallImageText.c_str(); // Tooltip for the small image
    UpdatePresence(discordPresence);
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
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.state = state; // The user's current state
    discordPresence.details = details; // The details of the activity
    discordPresence.largeImageKey = "cglarge"; // Key name of the large image asset
    discordPresence.largeImageText = "AAAA"; // Tooltip for the large image
    discordPresence.smallImageKey = "asset1"; // Key name of the small image asset
    discordPresence.smallImageText = "Look at his smile"; // Tooltip for the small image
    UpdatePresence(discordPresence);
}

void DiscordManager::SetDiscordPresence(std::string& details, std::string& state)
{
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));
    discordPresence.state = state.c_str(); // The user's current state
    discordPresence.details = details.c_str(); // The details of the activity
    discordPresence.largeImageKey = "cglarge"; // Key name of the large image asset
    discordPresence.largeImageText = "AAAA"; // Tooltip for the large image
    discordPresence.smallImageKey = "asset1"; // Key name of the small image asset
    discordPresence.smallImageText = "Look at his smile"; // Tooltip for the small image
    UpdatePresence(discordPresence);

}

void DiscordManager::UpdatePresence(DiscordRichPresence& pPresence)
{
    Discord_UpdatePresence(&pPresence);

}
