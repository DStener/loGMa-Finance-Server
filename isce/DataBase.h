#pragma once

namespace isce {
class DataBase {
	public:
		DataBase() {
			// INIT code
		}
		~DataBase() = default;

		static std::shared_ptr<DataBase> get() {
			static std::once_flag flag;
			static std::shared_ptr<DataBase> instance;
			std::call_once(flag, [&]() { instance.reset(new DataBase()); });
			return instance;
		}

		template<typename T>
		void Select() {
			// SELECT code
		}

		template<typename T>
		void Delete() {
			// DELETE code
		}

		template<typename T>
		void Insert() {
			// INSERT code
		}

		template<typename T>
		void Update() {
			// UPDATE code
		}
};
using DB = DataBase;
} // namespace isce