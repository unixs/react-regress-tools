import parser from '../lib/deps_parser';

describe('deps parser', () => {
  describe('async work based', () => {
    it('is defined', () => {
      expect(parser.parser).toBeDefined();
    });

    it('is function', () => {
      expect(typeof parser.parser).toBe('function');
    });

    it('return promise', async () => {
      const result = parser.parser({ str: "bbb" })
      expect(result.constructor.name).toBe("Promise");
    })

    it('return promise resolved with expected value', async () => {
      const result = parser.parser({ str: "bbb" })
      expect(await result).toBe("bbb");
    })
  });

  describe('pthread based', () => {
    it('is defined', () => {
      expect(parser.pthread_parser).toBeDefined();
    });

    it('is function', () => {
      expect(typeof parser.pthread_parser).toBe('function');
    });

    it('return promise', async () => {
      const result = parser.pthread_parser({ str: "bbb" })
      expect(result.constructor.name).toBe("Promise");
    })

    it('return promise resolved with expected value', async () => {
      const result = parser.pthread_parser({ str: "pthread ok" })
      expect(await result).toBe("pthread ok");
    })
  });
});
