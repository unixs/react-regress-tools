import parser from '../lib/deps_parser';

describe('deps parser', () => {
  it('be ok', () => {
    expect(parser.answer).toBe(42);
  });
});
