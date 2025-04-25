# Collectibles on Radar for GTA Vice City 🗺️

![radar](https://github.com/user-attachments/assets/6565978c-db16-4793-96e8-f7cea05a1f0a)


This ASI plugin shows GTA Vice City's collectibles on radar.

- Shows stores ![store](https://github.com/user-attachments/assets/fd0d0d31-1db8-47b5-b8f9-dca006549970), hidden packages ![hidden package](https://github.com/user-attachments/assets/9b2e21d2-a2e4-4c91-a544-c4cc928cad16), rampages ![rampage](https://github.com/user-attachments/assets/ad2adde2-3a70-40af-8180-4b84fcabfbbd) and unique stunt jumps ![usj](https://github.com/user-attachments/assets/d1bf7fec-6f57-4b29-be60-a075dd784a4d)
- Nearest collectible of each type always on the radar, even if outside radar's range
- Uses [DK22Pac's plugin-sdk](https://github.com/DK22Pac/plugin-sdk)
- This plugin can also show bribe, armour, weapon and health pickups (configurable in the INI file)
- NOTE: The stores and USJs aren't being read from the game memory as I'd like: the coords are hardcoded, and the collectible status is read from variables in the `main.scm` script
- NOTE: Mods that change the `main.scm` script could break stores and USJs
