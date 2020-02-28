var MyController = {};

MyController.init = function (id, debugging) {
    // turn on all LEDs
    print("test2", id, debugging)
}
 
MyController.shutdown = function() {
   // turn off all LEDs
    print(id)
}

// The wheel that actually controls the scratching
MyController.wheelTurn = function (channel, control, value, status, group) {
    // --- Choose only one of the following!
    var deckNumber = script.deckFromGroup(group);
    if (!engine.isScratching(deckNumber)) {
        var alpha = 0.8;
        var beta = alpha/32;
        engine.scratchEnable(deckNumber, 120, 33+1/3, alpha, beta);
    }

    value = value == 0 ? -1 : 1
    print("wheelTurn " + value + " " + deckNumber)

 
    // --- End choice
 
    // In either case, register the movement
    var deckNumber = script.deckFromGroup(group);
    engine.scratchTick(deckNumber, value); // Scratch!
    engine.setValue(group, 'jog', value); // Pitch bend
    engine.scratchDisable(deckNumber);

}

