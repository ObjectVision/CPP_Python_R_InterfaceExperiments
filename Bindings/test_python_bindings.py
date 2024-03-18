import numpy as np
from bin.x64.Release.PythonBindings import Engine

def test():
    engine = Engine()

    calculation_result = engine.Calculate()
    test_np_cast = np.array(calculation_result, copy = False)


    print(test_np_cast.shape)
    
    del engine

    print("Done processing")



if __name__ == "__main__":
    test()