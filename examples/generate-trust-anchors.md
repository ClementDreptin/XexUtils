# Generate Trust Anchors

## Download the certificate (example with Chrome)

- Go to the desired website.
- Click on "View site information" > "Connection is secure" > "Certicate is valid".
- Go to the details tab.
- Select the certificate of the CA that created the website's certificate.
- Click export.

## Create the C byte arrays from the certificate

Run the following command:

```
./brssl ta <certificate>
```

The `brssl` command-line tool can be built from the [BearSSL source](https://bearssl.org/#download-and-installation). On a Linux system, simply clone the repository and run `make`. The output binary will be in `build/brssl`. The same process might work on Windows, but I never tried.

The output will look something like this:

```C
static const unsigned char TA0_DN[] = {
    // ...
};

static const unsigned char TA0_EC_Q[] = {
    // ...
};

static const br_x509_trust_anchor TAs[1] = {
    {
        { (unsigned char *)TA0_DN, sizeof TA0_DN },
        BR_X509_TA_CA,
        {
            BR_KEYTYPE_EC,
            { .ec = {
                BR_EC_secp256r1,
                (unsigned char *)TA0_EC_Q, sizeof TA0_EC_Q,
            } }
        }
    }
};
```

You only need the byte arrays, the `br_x509_trust_anchor` struct is automatically created by the `AddXXXTrustAnchor` methods of `XexUtils::Socket` and `XexUtils::Http::Client`.
