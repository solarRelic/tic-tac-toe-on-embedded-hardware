# tic-tac-toe-on-embedded-hardware

Full task: https://cw.fel.cvut.cz/b222/courses/b35apo/en/semestral/start

Results Assessment

    registering team and submitting work specification (1 point at BRUTE semassign)
    basic functions to access and use peripherals, at least three different peripherals (3 points)
        use RGB LEDs for application output
        use 32 LED line for some state visualization
        output to serial port
        read from rotary dials knobs
        standard input (for example via SSH) without waiting to confirm of whole line by enter (raw input)
        read DC motor position and PWM control for DC motor extension kit
        processing of external events in interrupt service handler (applicable for QtMips only)
        system-call implementation (interrupt or exception service)
    text output to graphics LCD display/frame-buffer
        draw text with provided font (1 point)
        text output with proportional character width font and use of at least two fonts (1 point)
        line graphics or some other graphics visualization (1 point)
    application implements functional application logic according to the specification (5 point)
    quality of work, conformance to good coding practice rules (5 points)
        consistent indentation
        a function length should not exceed 20 or 30 lines - “one function has single well defined purpose” and name is descriptive
        divide application code to multiple files - each C source file should not exceed 150/200 lines
        select coding style and keep it for all code, inspiration PEP20 a např. Linux kernel coding style
    user interface/logic is ergonomic (3 points)
    documentation - obligatory, undocumented work is considered as void
        application architecture - block diagram (1 point)
        traceability, each function and global variable should be described and mapped to individual susbystem (1 point)
        user manual, it should allow full operation without other party assistance (1 point)
        description how to build (including dependencies) and start application (1 point)
    whole project development realized under version control system - GIT (voluntarily - awarded by bonus points)
        the project repository exists, it is not polluted (including history) by generated files (object files, binaries), if the work is proceed in pair, the commit from both parties witness real cooperation (1 bonus point)
        the commit brief and full description corresponds to the reason/purpose of the change (1 bonus point)
        each commit should add single feature or fix single problem
        development done in separated branch (“dev” for example) and before submission there is created merge request on gitlab (or github). Merge request is for integration of development/final project into “master” branch and is assigned to the teacher to allow efficient comment of the work. (1 bonus point)


