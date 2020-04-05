# echo2 for AmigaOS

echo2 is an enhanced version of the original echo command on AmigaOS. It allows you to easily center and border text, specify text color and style, add spacing, output text into a system requester or alert, plus more.

Originally started as a project in 1991 echo2 is finally being released to the public after all these years in hiding. It was designed for AmigaOS 1.3 and has been tested on other OS versions (see "Compatibility" section below).

Official website: [http://echo2.org](http://echo2.org)


## Usage

```
Usage: echo2 [<options>] "Your text"
  
  Supported HTML tags: <b>, <i>, <u>
  
  Options:
    -l<n,n>   n blank lines before and after text
    -s<n>     n spaces before text
    -p<n>     n character spacing
    -c        Center text
    -e        Clear screen first
    -f<n>     Foreground color [0-3]
    -b<n>     Background color [0-3]
    -o<n,n,n> Border style [1-2], padding l/r, t/b
    -d<n>     Text output speed [1-4], or specify no value to simulate typing
    -x        Flash screen
    -r        Show text in requester
    -a        Show text in alert
    -h        Show this help
```


## Compatibility

Following summarizes AmigaOS versions that echo2 has been tested on:

AmigaOS version | Compatibility
--------------- | -------------
1.2             | Untested
1.3             | Compatible
2.0             | Untested
3.0             | Compatible


## Examples

![Example #3](http://echo2.org/example-3.png "Example #3")

![Example #1](http://echo2.org/example-1.png?1 "Example #1")

![Example #2](http://echo2.org/example-2.png "Example #2")

![Example #4](http://echo2.org/example-4.png "Example #4")

See the /tests directory of this repository for a script containing more examples.  Install echo2 and then run the script using the execute command:

```
execute test
```


## Contributing

Your contributions to echo2 are welcome! echo2 is built in C using the Aztec v5.0a compiler. Download the development environment for WinUAE here: http://echo2.org/echo2_dev_hdd.zip


## Acknowledgments

Many thanks to @niklasekstrom for window/console expertise and wizardry!
