# Changelog

Notable changes to the Encave Restaurant Billing System are documented here.

## Unreleased

### Added
- Added classroom delivery and counter pickup options to the website and C++ console application.
- Added delivery details to generated receipts.
- Added an abstract `DeliveryOption` base class with `ClassroomDelivery` and `CounterPickup` implementations in C++ to demonstrate inheritance and runtime polymorphism.

### Changed
- Replaced the remaining “Chomp & Co.” branding in the C++ console application and receipt with “Encave.”
- Updated the C++ receipt address to match the website.
- Updated the README with delivery instructions and OOP concepts demonstrated by the project.

### Verified
- Compiled the C++ program successfully.
- Confirmed classroom delivery and counter pickup each display the correct description on the generated receipt.
