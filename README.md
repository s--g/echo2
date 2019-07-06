# echo2 for AmigaOS

echo2 is an enhanced version of the original echo command on AmigaOS. It allows you to easily center and border text, specify text color and style, add spacing, output text into a system requester or alert, plus more.

Originally started as a project in 1991 echo2 is finally being released to the public after all these years in hiding. It was designed for AmigaOS 1.3 and has been tested on other OS versions (see "Compatibility" section below).

Official website: [http://echo2.org](http://echo2.org)


## Usage

```
Usage: echo2 [<options>] "Your text"
    -l<n,n>   n blank lines before and after text
    -s<n>     n spaces before text
    -p<n>     n character spacing
    -c        Center text
    -e        Clear screen first
    -f<n>     Foreground color [0-3]
    -b<n>     Background color [0-3]
    -t<b,i,u> Font style [b]old, [i]talic, [u]nderline
    -o<n,n,n> Border style [1-2], padding l/r, t/b
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


## Contributing

Your contributions to echo2 are welcome! echo2 is built in C using the Aztec v5.0a compiler. I particularly need help in a couple of areas (such as detecting window column width and cli buffering) to finish off some existing features.

Download the development environment for WinUAE here: http://echo2.org/echo2_dev_hdd.zip
