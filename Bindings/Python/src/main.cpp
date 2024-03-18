#include <memory>

#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <pybind11/stl.h>

// Flow of test application:
//     Python:
//     -    constructs engine object
//     -    calls engine to perform primitive (reference counted) operation which returns matrix data: 1x1(scalar), 1xN(vector), MxN(matrix)
//     -        engine keeps reference to matrix data
//     -        engine returns view to matrix data
class Matrix {
public:
    Matrix(size_t rows, size_t cols) {
        init_unallocated_matrix(rows, cols);
    }

    Matrix(size_t rows, size_t cols, int32_t init_value) {
        init_unallocated_matrix(rows, cols);
        init_based_on_value(init_value);
    }

    int32_t* data() { return m_data.data(); }
    size_t rows() const { return m_rows; }
    size_t cols() const { return m_cols; }
    size_t size() const { return m_rows * m_cols; }

    std::shared_ptr<Matrix> Add(std::shared_ptr<Matrix> other)
    {
        assert(this->rows() == other->rows());
        assert(this->cols() == other->cols());

        std::shared_ptr<Matrix> result = std::make_shared<Matrix>(this->rows(), this->cols());
        for (int i=0; i<this->size(); i++)
        {
            result->data()[i] = this->m_data[i] + other->m_data[i];
        }
    	return result;
    }

private:
    void init_unallocated_matrix(size_t rows, size_t cols)
    {
        m_rows = rows;
        m_cols = cols;
        m_data.resize(rows * cols);// = new int32_t[rows * cols];
    }

    void init_based_on_value(int32_t init_value)
    {
        for (int i = 0; i < this->size(); i++) {
			m_data.at(i) = init_value;
		}
	}

    size_t m_rows = 0, m_cols = 0;
    std::vector<int32_t> m_data;
};

class Engine {
public:
    Engine() {}
    ~Engine() {
        // release reference to matrix data
        calc_results.clear();
    }

    std::shared_ptr<Matrix> Calculate() {
        size_t test_size = 50000;
		std::shared_ptr<Matrix> A = std::make_shared<Matrix>(test_size, test_size, 3);
        std::shared_ptr<Matrix> B = std::make_shared<Matrix>(test_size, test_size, 7);
		calc_results.push_back(A->Add(B));

        return calc_results.back();
	}
        
private:
    std::vector<std::shared_ptr<Matrix>> calc_results;
};

PYBIND11_MODULE(PythonBindings, m)
{
    pybind11::class_<Engine>(m, "Engine")
        .def(pybind11::init<>())
        .def("Calculate", &Engine::Calculate);


    pybind11::class_<Matrix>(m, "Matrix", pybind11::buffer_protocol()). //pybind11::array()). //  to restrict to numpy only ekse 
        def_buffer([](Matrix& m) -> pybind11::buffer_info {
            return pybind11::buffer_info(
                m.data(),                               /* Pointer to buffer */
                sizeof(int32_t),                          /* Size of one scalar */
                pybind11::format_descriptor<int32_t>::format(), /* Python struct-style format descriptor */
                2,                                      /* Number of dimensions */
                { m.rows(), m.cols() },                 /* Buffer dimensions */
                { sizeof(int32_t) * m.cols(),             /* Strides (in bytes) for each index */
                    sizeof(int32_t) }
            );
        });
}