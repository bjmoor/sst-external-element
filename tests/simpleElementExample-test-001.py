import sst

obj0 = sst.Component("simpleExternalElement0", "simpleExternalElement.SimpleExternalElement0")
obj0.addParams({
    "printFrequency" : "5",
    "repeats" : "15"
    })

obj1 = sst.Component("simpleExternalElement1", "simpleExternalElement.SimpleExternalElement1")
obj1.addParams({
    "printFrequency" : "5",
    "repeats" : "10"
    })

sst.Link("MyLink").connect( (obj0, "port", "15ns"), (obj1, "port", "15ns") )
