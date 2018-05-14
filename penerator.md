penerator(1) -- Generate a secure password over your local network
==================================================================

## SYNOPSIS

`penerator` [[[IP_ADDRESS]:]PORT]

## DESCRIPTION

Generate a secure password over your local network.

When GETting `/?<NUMBER>`, a secure (i.e. `/dev/urandom` as randomness source)
password of length `NUMBER` will be returned in plaintext.

## OPTIONS

  [[[IP_ADDRESS]:]PORT]

    Address to bind to.

    If IP_ADDRESS is not specified the listener will be bound to the specified
    port on all interfaces.

    Otherwise the listener will be bound to the specified port on the interface
    denoted by the IP_ADDRESS.

    Default: 8000.

## AUTHOR

Written by nabijaczleweli &lt;<nabijaczleweli@gmail.com>&gt;

## REPORTING BUGS

&lt;<https://github.com/nabijaczleweli/penerator/issues>&gt;

## SEE ALSO

&lt;<https://github.com/nabijaczleweli/penerator>&gt;
