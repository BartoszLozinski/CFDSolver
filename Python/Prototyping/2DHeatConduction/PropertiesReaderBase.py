from abc import ABC, abstractmethod

class PropertiesReaderBase(ABC):
    @classmethod
    def read_from_file(cls, filename):
        properties = cls._create_default_properties()
        properties_map = cls._create_properties_map()

        try:
            input_file = open(filename, "r", encoding="utf-8")
        except OSError as error:
            raise RuntimeError(
                f"Failed to open file for reading: {filename}"
            ) from error

        with input_file:
            for line in input_file:
                if not line.strip() or line.startswith("#"):
                    continue
                if line.strip() in ("{", "}"):
                    continue

                tokens = line.split()
                if len(tokens) < 2:
                    continue

                key, value = tokens[0], tokens[1]
                value = value.split("#", 1)[0]

                if key not in properties_map:
                    print(f"Unknown property found under {key} key.")
                    continue

                property_name, parser = properties_map[key]
                try:
                    setattr(properties, property_name, parser(value))
                except (TypeError, ValueError) as error:
                    raise RuntimeError(
                        f"Invalid value for property '{key}' "
                        f"in file {filename}"
                    ) from error

        return properties

    @classmethod
    @abstractmethod
    def _create_default_properties(cls):
        raise NotImplementedError

    @classmethod
    @abstractmethod
    def _create_properties_map(cls):
        raise NotImplementedError
