import parser from '../lib/deps_parser';

describe('deps parser', () => {

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
