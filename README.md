# Qt-Pamietnik

Qt-Pamietnik is an application built using Qt, that allows user the creation, storage, and retrieval of custom text entries with or without photos. Code has been written in a three-layer architecture, 
separting user interface from data management, and using a middle layer to pass data between them.

# Features
- Create text entries, with selectable styles like bold, italic or colors.
- Possibility for adding images for every entry.
- Save and load created entries

# Overview
Once you start application, you can choose to either create new entry or load existing saved state.

![StartingScreen](https://github.com/PawSikora/Qt-Pamietnik/assets/72358883/1b579226-93dd-4d42-8eb0-95bfd620db7f)

After selecting "Dodaj wpis" you are transported to editing screen, where you can type your journal entry, select style for entire text or add a picture visualising your entry.

![EditingEntryScreen](https://github.com/PawSikora/Qt-Pamietnik/assets/72358883/b5bd47e6-842b-43fe-bf41-cc2395120e39)

Here's the main screen after adding couple of entries which are sorted chronologically.

![MainScreenWithEntries](https://github.com/PawSikora/Qt-Pamietnik/assets/72358883/7d68fed3-fbb5-48fe-b791-b487e00b3f5f)

There's also a possiblity to delete entry.

![DeletingEntry](https://github.com/PawSikora/Qt-Pamietnik/assets/72358883/617c1fdd-1f53-4778-b43c-55f616d8e62f)

When choosing to "Zapisz kopie" you are prompted with dialogue option to choose location of saved .txt file that stores current journal state.

Choosing "Wczytaj kopie" allows for loading file that will restore saved state.
