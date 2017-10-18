# c-hangman - a program that persistently tracks user statistics & adjusts gameplay based on skill level

This is a C-based program that plays Hangman, while tracking each individual user's performance and adjusting the difficulty of the challenge words as they play, based on their performance. Statistics are kept persistently in text files associated with the user and are used to calculate appropriate words from a given dictionary file.

A port of this program to Python can be found [here.](https://github.com/MattMiles/py-hangman)

## Setting up the dictionary file

This program requires a text file of words to be used for gameplay. This file must be a simple string of words separated by newline characters, as such:

```
foo
bar
baz
```

Name this file dictionary.txt and place it in the project's root directory.

On startup, these words will be read and categorized as easy, medium, and hard, and be used as challenge words in the game.

## License

This project is licensed under the GNU General Public License 3.0. See the license for more details.
