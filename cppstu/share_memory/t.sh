echo 'niuniu niumei' | grep -oE "niuniu|niumei" | awk '{
    print "Start" 
    print $0 
    next 
    print "End"}'
