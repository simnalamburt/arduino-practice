Arduino Practice [![Build Status]][travis]
========
Please use [PlatformIO](http://platformio.org/) to build and execute project.
```bash
python3 -m venv .venv && . .venv/bin/activate && pip install -U pip setuptools
pip install -r requirements.txt

# Build project
platformio run

# Upload to connected Arduono machine
platformio run -t upload

# Monitor serialports
platformio serialports monitor
```

[Build Status]: https://travis-ci.org/simnalamburt/arduino-practice.svg?branch=master
[travis]: https://travis-ci.org/simnalamburt/arduino-practice
