# Mobile Operators

## Overview

Mobile Operators is a Qt-based desktop application designed to display and manage a list of mobile network operators organized by their countries. The application allows users to view, add, edit, and delete operators through an intuitive Qt Quick (QML) interface.

## Technologies Used

- Qt 6.x (QtQuick, QML, QtSql)
- SQLite (embedded database)
- C++ (business logic and model)
- CMake (build system)

## Architecture

The project follows the Model-View-ViewModel (MVVM) pattern:

- **Model**: `DataStorage` — Manages raw data loaded from DB and related operations on it.
- **ViewModel**: `CombinedModel` — Extends `QAbstractItemModel` to expose data and handle UI interactions.
- **View**: QML UI components — Presents the tree view and dialogs for user interaction.

Additionally the project also contains 'SqlManager' — A singleton class that is responsible for any DB interaction, including setting the connection and sending the queries

## Features

- View countries and their operators in a hierarchical TreeView.
- Add new operators to countries.
- Edit existing operator names.
- Delete operators from the list and database.

## Examples


