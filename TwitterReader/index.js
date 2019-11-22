const SerialPort = require("serialport");
const Twit = require('twit')

let T = new Twit({
    consumer_key: '...',
    consumer_secret: '...',
    access_token: '...',
    access_token_secret: '...',
    timeout_ms: 60 * 1000,  // optional HTTP request timeout to apply to all requests.
    strictSSL: true,     // optional - requires SSL certificates to be valid.
});

let stream = T.stream('statuses/filter', { track: '#gameboytwitter', language: 'en' })

let sp = new SerialPort("/dev/cu.usbmodem142101", {
    baudRate: 9600
}, false);

console.log("Serial Port Connecting");

sp.open(((err) => {
    setTimeout(() => {
        console.log("Connected");

        stream.on('tweet', (tweet) => {
            console.log(tweet.text);
            let removedHashtag = tweet.text.replace('#gameboytwitter', '');
            let trimmedText = removedHashtag.substring(0, 39);
            let escaped = trimmedText + "\n";
            sp.write(escaped, ((err, res) => {
                if (err) { console.log(err); }
            }));
        });
    }, 5000);
}));
