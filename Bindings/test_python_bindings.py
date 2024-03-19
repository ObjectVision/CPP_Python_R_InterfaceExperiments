import numpy as np
from bin.x64.Release.PythonBindings import Engine

def test_reference_return_policy():
    engine = Engine()
    calculation_result = engine.Calculate()
    np_array = np.array(calculation_result, copy = False)
    return

def test_memory_view():
    engine = Engine()
    calculation_view   = engine.CalculateView()
    view_array = np.array(calculation_view, copy=False)
    return

def test():
    engine = Engine()

    test_reference_return_policy()

    test_memory_view()

    print("Done processing")



if __name__ == "__main__":
    test()